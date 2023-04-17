#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 8

/* Structure de nœud pour l'arbre */
struct TreeNode {
    int value;                  /* La valeur stockée dans le nœud */
    struct TreeNode *parent;    /* Pointeur vers le parent */
    struct TreeNode *child;     /* Pointeur vers le premier enfant */
    struct TreeNode *sibling;   /* Pointeur vers le frère suivant */
};

/* Structure de graphe pour stocker les relations de sommet */
struct Graph {
    int num_nodes;          /* Le nombre de sommets dans le graphe */
    int adj_matrix[MAX_NODES][MAX_NODES];   /* La matrice d'adjacence */
};

/* Initialiser un nœud avec une valeur donnée */
struct TreeNode* init_node(int value) {
    struct TreeNode *node = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    node->value = value;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

/* Ajouter un enfant à un nœud */
void add_child(struct TreeNode *parent, struct TreeNode *child) {
    child->parent = parent;
    if (parent->child == NULL) {
        parent->child = child;
    } else {
        struct TreeNode *sibling = parent->child;
        while (sibling->sibling != NULL) {
            sibling = sibling->sibling;
        }
        sibling->sibling = child;
    }
}

void print_tree(struct TreeNode *node, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%d\n", node->value);
    struct TreeNode *child = node->child;
    while (child != NULL) {
        print_tree(child, depth + 1);
        child = child->sibling;
    }
}

/* Parcours en profondeur d'abord pour la recherche d'un arbre de recouvrement */
void dfs(struct Graph *graph, int node, struct TreeNode *parent, bool visited[], struct TreeNode **tree_nodes, int *num_tree_nodes) {
    /* Marquer le nœud comme visité */
    visited[node] = true;

    /* Ajouter le nœud au nouvel arbre de recouvrement */
    struct TreeNode *tree_node = init_node(node);
    add_child(parent, tree_node);
    tree_nodes[*num_tree_nodes] = tree_node;
    (*num_tree_nodes)++;

    /* Explorer les voisins non visités */
    for (int i = 0; i < graph->num_nodes; i++) {
        if (graph->adj_matrix[node][i] != 0 && !visited[i]) { // Ajouter une vérification pour éviter les nœuds déjà visités
            /* Trouver un voisin non visité */
            graph->adj_matrix[node][i] = 0;
            dfs(graph, i, tree_node, visited, tree_nodes, num_tree_nodes);
        }
    }
}

/* Recherche de l'arbre de recouvrement pour un graphe connexe */
struct TreeNode* find_spanning_tree(struct Graph *graph) {
    /* Initialiser la structure d'arbre */
    struct TreeNode *root = init_node(0);
    struct TreeNode *tree_nodes[MAX_NODES];
    int num_tree_nodes = 0;
    tree_nodes[num_tree_nodes] = root;
    num_tree_nodes++;

    /* Parcourir le graphe avec une recherche en profondeur d'abord */
    bool visited[MAX_NODES] = {false};  // tableau de booléens pour stocker les sommets visités
    dfs(graph, 0, root, visited, tree_nodes, &num_tree_nodes);

    return root;
}




/* Fonction de test pour vérifier la recherche de l'arbre de recouvrement */
int main() {
    /* Initialiser la matrice d'adjacence */
    int adj_matrix[MAX_NODES][MAX_NODES] = {
        {0, 0, 36, 0, 0, 19, 0, 0},
        {0, 0, 0, 0, 0, 0, 50, 43},
        {36, 0, 0, 56, 55, 31, 0, 36},
        {0, 0, 56, 0, 0, 0, 15, 0},
        {0, 0, 55, 0, 0, 0, 0, 0},
        {19, 0, 31, 0, 0, 0, 37, 52},
        {0, 50, 0, 15, 0, 37, 0, 0},
        {0, 43, 36, 0, 0, 52, 0, 0}
    };

    int num_nodes = 8;

    /* Initialiser le graphe */
    struct Graph graph;
    graph.num_nodes = num_nodes;
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            graph.adj_matrix[i][j] = adj_matrix[i][j];
        }
    }

    /* Trouver un arbre de recouvrement */
    struct TreeNode *root = find_spanning_tree(&graph);

    /* Afficher l'arbre de recouvrement */
    printf("Root node: %d\n", root->value);
    printf("Children of root node:\n");
    print_tree(root, 1);

    return 0;
}






