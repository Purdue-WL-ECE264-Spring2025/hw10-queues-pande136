#include "queue.h"

#include "tile_game.h"


void enqueue(struct queue *q, struct game_state state) {

    uint64_t serialized = serialize(state);

    insert_at_tail(&q->data, serialized);

}


struct game_state dequeue(struct queue *q) {

    uint64_t serialized = remove_from_head(&q->data); 

    return deserialize(serialized);

}


bool is_empty(const struct queue *q) { 

    return q->data.head == NULL; 

}


void free_queue(struct queue *q) {

    free_list(q->data);

    q->data.head = NULL;

}


//helper function to determine if a certain state is solved

bool is_solved(struct game_state state) {

    int expected = 1;

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            if (i == 3 && j == 3) {

                if (state.tiles[i][j] != 0) {

                    return false;

                }

            } 

            else {

                if (state.tiles[i][j] != expected) {

                    return false;

                }

                expected++;

            }

        }

    }

    return true;

}


// helped function to generate neighbor states

void generate_neighbors(struct game_state state, struct queue *neighbors) {

    int row = state.empty_row;

    int col = state.empty_col;

    

    int dr[] = {-1, 1, 0, 0}; // changes made to row

    int dc[] = {0, 0, -1, 1}; // changes made ot columns


    for (int i = 0; i < 4; i++) {

        int new_row = row + dr[i];

        int new_col = col + dc[i];

        if (new_row >= 0 && new_row < 4 && new_col >=0 && new_col < 4) {

            struct game_state new_state = state;

            new_state.tiles[row][col] = state.tiles[new_row][new_col];

            new_state.tiles[new_row][new_col] = 0;

            new_state.empty_row = new_row;

            new_state.empty_col = new_col;

            new_state.num_steps++;

            enqueue(neighbors, new_state);

        }

    }

}


int number_of_moves(struct game_state start) { 

    if (is_solved(start)) {

        return 0;

    }

    struct queue q = {0}; // states to be visited

    struct queue visited = {0}; // states that have been visited


    enqueue(&q, start);

    uint64_t start_serialized = serialize(start);

    insert_at_tail(&visited.data, start_serialized);


    while (!is_empty(&q)) {

        struct game_state current = dequeue(&q);

        if (is_solved(current)) {

            free_queue(&q);

            free_queue(&visited);

            return current.num_steps;

        }


        struct queue neighbors = {0};

        generate_neighbors(current, &neighbors);


        while (!is_empty(&neighbors)) {

            struct game_state next = dequeue(&neighbors);

            uint64_t serialized_next = serialize(next);

            bool found = false;

            struct list_node *temp = visited.data.head;

            while (temp != NULL) {

                if (temp->value == serialized_next) {

                    found = true;

                    break;

                }

                temp = temp->next;

            }

            if (!found) {

                enqueue(&q, next);

                insert_at_tail(&visited.data, serialized_next);

            }

        }

        free_queue(&neighbors);

    }

    free_queue(&visited);



    return -1; 

}
