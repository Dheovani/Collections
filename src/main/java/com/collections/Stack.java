package com.collections;

public class Stack {

    private int top;
    private Object stack[];

    public Stack(int size) {
        this.stack = new Object[size];
        this.top = 0;
    }

    public int getTop() {
        return top;
    }

    public Object[] getStack() {
        return stack;
    }

    public boolean isEmpty() {
        return this.top == 0;
    }

    public boolean isFull() {
        return this.stack.length == this.top;
    }

    public void push(Object value) throws IndexOutOfBoundsException {
        if (isFull()) {
            throw new IndexOutOfBoundsException("Pilha cheia");
        }

        this.stack[top] = value;
        this.top += 1;
    }

    public Object pop() throws IndexOutOfBoundsException {
        if (isEmpty()) {
            throw new IndexOutOfBoundsException("Pilha vazia");
        }

        this.top -= 1;
        Object oldTop = this.stack[top];
        this.stack[top] = null;

        return oldTop;
    }

    public Object find(Object value) {
        return value;
    }
    
}
