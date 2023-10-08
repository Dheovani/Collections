package com.collections;

import java.util.EmptyStackException;

public class StaticList {

    private int head;
    private int tail;
    private Object[] array;

    public StaticList(int size) {
        this.head = -1;
        this.tail = -1;
        this.array = new Object[size];
    }

    /**
     * Verifica se a fila está vazia
     * @return boolean
     */
    public boolean isEmpty() {
        return this.head == -1 && this.tail == -1;
    }

    /**
     * Verifica se a fila está cheia
     * @return boolean
     */
    public boolean isFull() {
        return (this.tail + 1) % this.array.length == this.head;
    }

    /**
     * Adiciona um valor à fila
     * @param value
     * @throws StackOverflowError
     * @return void
     */
    public void add(Object value) {
        if (isFull()) {
            throw new StackOverflowError("A fila anda");
        }

        this.tail = (this.tail + 1) % this.array.length;
        this.array[this.tail] = value;

        if (this.head == -1) {
            this.head = this.tail;
        }
    }

    /**
     * Retorna e remove um elemento da fila
     * @throws EmptyStackException
     * @return Object
     */
    public Object delete() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }

        Object value = this.array[this.head];

        if (this.head == this.tail) {
            this.head = -1;
            this.tail = -1;
        } else {
            this.head = (this.head + 1) % this.array.length;
        }

        return value;
    }

    /**
     * Limpa a fila
     * @retun void
     */
    public void clean() {
        this.head = -1;
        this.tail = -1;
    }

    /**
     * Percorre todos os elementos da fila e printa eles
     * @return void
     */
    public void run() {
        int cont = this.head;

        do {
            System.out.println(this.array[cont]);
            cont = (cont + 1) % this.array.length;
        } while (cont != this.tail);

        System.out.println(this.array[cont]);
    }
    
}
