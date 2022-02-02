import numpy               as np
import tensorflow          as tf

#########################################
# Lower star filtration on simplex tree #
#########################################

# The parameters of the model are the vertex function values of the simplex tree.

def _LowerStarSimplexTree(simplextree, filtration, dimensions):
    # Parameters: simplextree (simplex tree on which to compute persistence)
    #             filtration (function values on the vertices of st),
    #             dimensions (homology dimensions),
    
    simplextree.reset_filtration(-np.inf, 0)

    # Assign new filtration values
    for i in range(simplextree.num_vertices()):
        simplextree.assign_filtration([i], filtration[i])
    simplextree.make_filtration_non_decreasing()
    
    # Compute persistence diagram
    simplextree.compute_persistence()
    
    # Get vertex pairs for optimization. First, get all simplex pairs
    pairs = simplextree.lower_star_persistence_generators()
    
    L_indices = []
    for dimension in dimensions:
    
        finite_pairs = pairs[0][dimension] if len(pairs[0]) >= dimension+1 else np.empty(shape=[0,2])
        essential_pairs = pairs[1][dimension] if len(pairs[1]) >= dimension+1 else np.empty(shape=[0,1])
        
        finite_indices = np.array(finite_pairs.flatten(), dtype=np.int32)
        essential_indices = np.array(essential_pairs.flatten(), dtype=np.int32)

        L_indices.append((finite_indices, essential_indices))

    return L_indices

class LowerStarSimplexTreeLayer(tf.keras.layers.Layer):
    """
    TensorFlow layer for computing lower-star persistence out of a simplex tree
    """
    def __init__(self, simplextree, dimensions, min_persistence=None, **kwargs):
        """
        Constructor for the LowerStarSimplexTreeLayer class
  
        Parameters:
            simplextree (gudhi.SimplexTree): underlying simplex tree. Its vertices MUST be named with integers from 0 to n = number of vertices
            dimensions (List[int]): homology dimensions
            min_persistence (List[float]): minimum distance-to-diagonal of the points in the output persistence diagrams (default None, in which case 0. is used for all dimensions)
        """
        super().__init__(dynamic=True, **kwargs)
        self.dimensions  = dimensions
        self.simplextree = simplextree
        self.min_persistence = min_persistence if min_persistence != None else [0. for _ in range(len(self.dimensions))] 
        assert len(self.min_persistence) == len(self.dimensions)

    def call(self, filtration):
        """
        Compute lower-star persistence diagram associated to a function defined on the vertices of the simplex tree

        Parameters:
            F (TensorFlow variable): filter function values over the vertices of the simplex tree. The ith entry of F corresponds to vertex i in self.simplextree

        Returns:
            dgms (list of tuple of TensorFlow variables): list of lower-star persistence diagrams of length self.dimensions, where each element of the list is a tuple that contains the finite and essential persistence diagrams of shapes [num_finite_points, 2] and [num_essential_points, 1] respectively
        """
        # Don't try to compute gradients for the vertex pairs
        indices = _LowerStarSimplexTree(self.simplextree, filtration.numpy(), self.dimensions)
        # Get persistence diagrams
        self.dgms = []
        for idx_dim, dimension in enumerate(self.dimensions):
            finite_dgm = tf.reshape(tf.gather(filtration, indices[idx_dim][0]), [-1,2])
            essential_dgm = tf.reshape(tf.gather(filtration, indices[idx_dim][1]), [-1,1])
            min_pers = self.min_persistence[idx_dim]
            if min_pers >= 0:
                persistent_indices = np.argwhere(np.abs(finite_dgm[:,1]-finite_dgm[:,0]) > min_pers).ravel()
                self.dgms.append((tf.gather(finite_dgm, indices=persistent_indices), essential_dgm))
            else:
                self.dgms.append((finite_dgm, essential_dgm))
        return self.dgms

