#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    bool* seats;
    int size;
    int min;
} SeatManager;

SeatManager* seatManagerCreate(int n) {
    SeatManager* obj = malloc(sizeof(SeatManager));
    obj->seats = calloc((n + 1), sizeof(bool));
    obj->size = n + 1;
    obj->min = 1;
    return obj;
}

int seatManagerReserve(SeatManager* obj) {

    int ret = obj->min;
    (obj->seats)[ret] = true;

    while (obj->min < obj->size && obj->seats[obj->min] != false)
        obj->min++;

    return ret;
}

void seatManagerUnreserve(SeatManager* obj, int seatNumber) {
    obj->seats[seatNumber] = false;
    obj->min = fmin(obj->min, seatNumber);
    return;
}

void seatManagerFree(SeatManager* obj) {
    free(obj->seats);
    free(obj);
}

int main() {
    int n = 5; // Número de assentos
    SeatManager* manager = seatManagerCreate(n);

    printf("Reserva feita: %d\n", seatManagerReserve(manager)); 
    printf("Reserva feita: %d\n", seatManagerReserve(manager));
    
    seatManagerUnreserve(manager, 1); // Libera o assento 1
    printf("Reserva desfeita: %d\n", seatManagerReserve(manager)); 
    
    printf("Reserva feita: %d\n", seatManagerReserve(manager)); 
    printf("Reserva feita: %d\n", seatManagerReserve(manager)); 
    printf("Reserva feita: %d\n", seatManagerReserve(manager)); 
    
    seatManagerUnreserve(manager, 3); // Libera o assento 3
    printf("Reserva desfeita: %d\n", seatManagerReserve(manager));
    
    seatManagerFree(manager);
    return 0;
}