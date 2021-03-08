#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ActionI {
    int type;
    int payload;
};

struct ActionI * newAction(int type, int payload) {
    struct ActionI *self = (struct ActionI *) malloc(sizeof(struct ActionI));

    self->type = type;
    self->payload = payload;

    return self;
}

struct Store {
    int (*reducer)(int state, struct ActionI *);
    void (*dispatch)(struct Store *, struct ActionI *);
    int cont;
};

struct Store * newStore(
    int (*reducer)(int state, struct ActionI *),
    void (*dispatch)(struct Store *, struct ActionI *),
    int cont
) {
    struct Store *self = (struct Store *)malloc(sizeof(struct Store));

    self->cont = cont;
    self->reducer = reducer;
    self->dispatch = dispatch;

    return self;
}

void dispatch(struct Store *store, struct ActionI *action) {
    int newState = store->reducer(store->cont, action);
    store->cont = newState;
}

int reducer(int state, struct ActionI *action) {
    switch (action->type){
        case 1:
            return state + action->payload;
        case 0:
            return state - action->payload;
        default:
            return state;
    }
}

int main() {
    struct ActionI *add = (struct ActionI *) newAction(1, 1);

    struct Store *store = (struct Store *) newStore(&reducer, &dispatch, 0);

    printf("inicial state: %d\n", store->cont);

    store->dispatch(store, add);

    printf("final state: %d\n", store->cont);

    return 0;
}