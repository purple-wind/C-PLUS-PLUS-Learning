#include <iostream>
#include <string>

// This approach adds one bit to end and start pointers
// Circular buffer object
typedef struct {
    int size; // maximum number of elements
    int start; // index of oldest element
    int end; // index at which to write new element
    int *elems; // vector of elements
} CircularBuffer;

void cbInit(CircularBuffer *cb, int size) {
    cb->size = size;
    cb->start = 0;
    cb->end = 0;
    cb->elems = (int *)calloc(cb->size, sizeof(int));
}

void cbPrint(CircularBuffer *cb) {
    printf("size = 0x%x, start = %d, end = %d\n", cb->size, cb->start, cb->end);
}

//start end相差size个位置则表示缓冲区满了
int cbIsFull(CircularBuffer *cb) {
    return (cb->end - cb->start == cb->size | cb->start - cb->end == cb->size) ? 1 : 0;
    //当size为2的幂时，等价于上面，上面的方式更通用，在size不为2的幂时也可正常工作，但是效率更低
    //return cb->end == (cb->start ^ cb->size); // This inverts the most significant bit of start before comparison
}

int cbIsEmpty(CircularBuffer *cb) {
    return cb->end == cb->start;
}

int cbIncr(CircularBuffer *cb, int p) {
    return (p + 1) % (2 * cb->size);
    //当size为2的幂时，等价于上面，上面的方式更通用，在size不为2的幂时也可正常工作，但是效率更低
    //return (p + 1) & (2 * cb->size - 1); // start and end pointers incrementation is done modulo 2*size
}

void cbWrite(CircularBuffer *cb, int *elem) {
    cb->elems[cb->end % cb->size] = *elem;
    //当size为2的幂时，等价于上面，上面的方式更通用，在size不为2的幂时也可正常工作，但是效率更低
    //cb->elems[cb->end & (cb->size - 1)] = *elem;

    if (cbIsFull(cb)) // full, overwrite moves start pointer
        cb->start = cbIncr(cb, cb->start);
    cb->end = cbIncr(cb, cb->end);
}

void cbRead(CircularBuffer *cb, int *elem) {
    if(cbIsEmpty(cb))
    {
        return;
    }
    *elem = cb->elems[cb->start % cb->size];
    //当size为2的幂时，等价于上面，上面的方式更通用，在size不为2的幂时也可正常工作，但是效率更低
    //*elem = cb->elems[cb->start & (cb->size - 1)];
    cb->start = cbIncr(cb, cb->start);
}


int main(int argc, char *argv[])
{

    CircularBuffer g_circ_buffer;
    cbInit(&g_circ_buffer, std::stod(argv[1]));

    cbPrint(&g_circ_buffer);
    std::cout<<"isempty="<<cbIsEmpty(&g_circ_buffer)<<" isfull="<<cbIsFull(&g_circ_buffer)<<std::endl;

    for(int i = 0; i < std::stod(argv[2]); i++)
    {
        int* element = new int(i);
        cbWrite(&g_circ_buffer, element);
        //std::cout<<"e="<<*element<<" empty="<<cbIsEmpty(&g_circ_buffer)<<" full="<<cbIsFull(&g_circ_buffer)<<" start="<<g_circ_buffer.start<<" end="<<g_circ_buffer.end<<std::endl;
    }
    cbPrint(&g_circ_buffer);

    for(int i = 0; i < 5; i++)
    {
        int* element = new int(100);
        cbRead(&g_circ_buffer, element);
        std::cout<<"element="<<*element<<std::endl;
    }
    cbPrint(&g_circ_buffer);
    std::cout<<"isempty="<<cbIsEmpty(&g_circ_buffer)<<std::endl;

}
