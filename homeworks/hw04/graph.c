#include "graph.h"


// This function initializes an adjacency list for
// a graph.
// 
// Note that adj list is an array of """adj_node_t*""" which is passed
// in by reference.
// That is, you are passing in a pointer (i.e, *) to an array (i.e., *)
// of adj_node_t*, which is why list is of type adj_node_t***
void init_adj_list(adj_node_t ***list, int rows)
{
    // Part 2 - Fill in this function
    	// Initialize i, malloc *list as it is passed in as a pointer. 
	// Loop through each row index of list and set to NULL
	int i;
	*list = malloc(sizeof(adj_node_t*) * rows);
	for(i = 0; i < rows; ++i) {
		(*list)[i] = NULL;
	}
}



// This function creates a new adj_node_t node
// and initializes it with node->vid = vid
// and node->next = NULL;
// The function then returns this node
adj_node_t *create_node(int vid)
{
    // Part 3 - Fill in this function
        // Malloc for sizeof node, and set values of node accordingly
	// set next to NULL
	adj_node_t *node = (adj_node_t*) malloc(sizeof(adj_node_t));
	node->vid = vid;
	node->next = (adj_node_t*) NULL;
	return node;
}


// Pass in the list and the row to which you need to add a new node
// First check that the adjacency list for the current row is not
// empty (i.e., NULL). If it is NULL, it is the first adjacent node.
// Otherwise, traverse the list until you reach the end, and then add
// the new node
void add_node(adj_node_t** list, int row, adj_node_t* node)
{
    // Part 4 - Fill in this function;
    	// If row is -1, means that we are using as enqueue for bfs function
	if (row == -1) {
		// make y the first node of list, iterate until next = NULL and set
		adj_node_t *y = *list;
		while (y->next != NULL) {
			y = y->next;
		}
		y->next = node;
		return;
	}
	// Implement same as above but looping through the correct row
	if (list[row] != NULL) {
		adj_node_t *x = list[row];
		while(x->next != NULL) {
			x = x->next;
		}
		x->next = node;
		return;
	} else {
		list[row] = node;
		return;
	}
}

// deqeueu a node from a queue
// and return the vertex id of the first member
// when list returns, it points to the next member in the queue
int remove_node(adj_node_t **list)
{
    // Part 6 - Implement this function
    	// Val is return vid, if next is null then return -2 for use in bfs
	// Else set x = next, and set val to the vode that will be removed
	// If x->next is null then set (*list)->next as NULL
	// else set to next node, and free x
	int val;
	if ((*list)->next != NULL) {
		adj_node_t *x = (*list)->next;
		val = x->vid;
		if (x->next != NULL) {
			(*list)->next = x->next;
			free(x);
		} else {
			(*list)->next  = NULL;
		}
	} else {
		(*list)->vid = -2;
		val = (*list)->vid;
	}
	return val;
}


// This function constructs an adjacency list for a graph.
//
// adj_mat is a 2D array that represents the adjacency matrix
//
// list is passed in by reference from the main function so that
// it can be malloc'd via the init_adj_list function (see aobve)
//
// After initializing it go through each row and add its adjacent 
// nodes
void construct_adj_list(int **adj_mat, int rows, int cols, adj_node_t ***list)
{
    // verify that the adj matrix is correct
    if(rows != cols) {
        printf("Adjacency matrix is not square\n");
        exit(EXIT_FAILURE);
    }

    init_adj_list(list, rows);
    // Part 1 - Fill in the rest of this function
	// Initialize vars, and loo[ through each row and col
	// if there is a 1 in [row][col] then create node j and add to row i;
    	int i, j;
	adj_node_t *node;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			if(adj_mat[i][j] != 0) {
				node = create_node(j);
				add_node(*list, i, node);
			}
		}
		free(adj_mat[i]);
	}
	free(adj_mat);
    // You will need to implement create_node() and
    // add_node() and use them to implement this function
}

// This takes in an adjacency ilst and prints out the list
void print_adj_list(adj_node_t **list, int rows)
{
    assert(list);

    printf("---- Print Adj. List ----\n");
    for(int i = 0; i < rows; i++) {
        printf("|%d| -> ", i);
        adj_node_t* next = list[i];
        while(next != NULL) {
            printf("%d -> ", next->vid);
            next = next->next;
        }
        printf("END\n");
    }
    printf("--------\n\n");
}

void free_adj_list(adj_node_t **list, int rows)
{
    // Part 7 - Implement this function
    	// Initialize vars and loop through each row
	// Set node = list[row]
	int i;
	adj_node_t *node, *current;
	for (i = 0; i < rows; ++i) {
		node = list[i];
		// If node has no next then just free node
		while(node->next != NULL) {
			// Set current = next node
			current = node->next;
			if(current->next == NULL) {
				// If next from current is NULL, free current
				// Then free next, node is freed after while
				free(current->next);
				free(current);
				node->next = NULL;
				free(node->next);
			} else {
				// set node->next = current->next and free current
				node->next = current->next;
				current->next = NULL;
				free(current->next);
				free(current);
			}
		}
		free(node);
	}
	// Free the whole list
   	free(list); 
}

void print_bfs_result(int rows, int *color, int *distance, int *parent)
{
    assert(color);
    assert(distance);
    assert(parent);

    printf("---- Print BFS Result ----\n");
    printf("Vert\tCol\tDis\tParent\n");
    for(int i = 0; i < rows; i++) {
        printf("%d\t%d\t%d\t%d\n", i, color[i], distance[i], parent[i]);
    }
    printf("--------\n\n");
}


// Do BFS here, given the source node and the
// graph's adjacency list
int bfs(adj_node_t **list, int rows, int source,
        int *color, int *distance, int *parent)
{
    // Make sure the source is a valid vertex
    if(source >= rows) {
        printf("Invalid source vertex\n");
        return 0;
    }
    // Make sure the adjacency list is not empty
    if(list == NULL) {
        printf("There is nothing in the adjacency list\n");
        return 0;
    }
    // Make sure all these are properly allocated
    assert(color);
    assert(distance);
    assert(parent);

    // Part 5 - Fill in the rest of this function
	// Initialize color, distance, and parent to respective NULL/0/INF
    	int i;
	for(i = 0; i < rows; ++i) {
		if(i != source) {
			color[i] = 0;
			distance[i] = (2^31) - 1;
			parent[i] = -1;
		}
	}
	color[source] = 1;
	distance[source] = 0;
	parent[source] = -1;
	
	// Make a Queue and initialize with s
	int u = -2;
	adj_node_t *v1, *v2;
	adj_node_t *Q = create_node(-1);
	adj_node_t *s = create_node(source);
	add_node(&Q,-1,s);
	// while Q vid is -1 which allows for error checking with -2 in remove
	while(Q->vid == -1) {
		// u represents vid of node start
		u = remove_node(&Q);
		// if u is -2 set v1 = NULL to bypass next while, and bypass setting color
		if (u == -2){
			v1 = NULL;
		// else set v1 = to list[u], essentially first u->v pair.
		} else {
			v1 = list[u];
		}
		// Loop through adjacent nodes by setting v1 to v1->next each loop
		while(v1 != NULL) {
			// if not visited color and adjust data, else ignore and set v1 = v1->next
			if(color[v1->vid] == 0) {
				color[v1->vid] = 1;
				distance[v1->vid] = distance[u] + 1;
				parent[v1->vid] = u;
				v2 = create_node(v1->vid);
				add_node(&Q, -1, v2);
			}
			v1 = v1->next;
		} 
		// Bypassed if Q is empty
		if(u != -2) {
			color[u] = 2;	
		}
	}
	// Free vars used
	free(v1);
	free(v2->next);
	free(v2);
	free(s->next);
	free(s);
	free(Q->next);
	free(Q);
    #if DEBUG
    print_bfs_result(rows, color, distance, parent);
    #endif

    return 0;
}






