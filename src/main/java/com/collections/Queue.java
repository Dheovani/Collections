package com.collections;

import java.util.function.Consumer;

public class Queue<T> {

    private Element head;
    private Element tail;

    public Queue() {
        this.head = null;
        this.tail = null;
    }

    /**
     * Verifica se a fila esta vazia
     * @return boolean
     */
    public boolean isEmpty() {
        return this.head == null && this.tail == null;
    }

    /**
     * Adiciona um elemento ao inicio da fila
     * @param value
     */
    public void add(T value) {
        Element element = new Element(value);
        element.setNext(this.head);

        if (this.isEmpty()) {
            this.tail = element;
        } else {
            this.head.setPrevious(element);
        }
        
        this.head = element;
    }

    /**
     * Adiciona um elemento ao final da fila
     * @param value
     */
    public void append(T value) {
        Element element = new Element(value);
        element.setPrevious(this.tail);

        if (this.isEmpty()) {
            this.head = element;
        } else {
            this.tail.setNext(element);
        }

        this.tail = element;
    }

    /**
     * Deleta o primeiro elemento da fila
     * @return T
     * @throws EmptyQueueException
     */
    public T delete() throws EmptyQueueException {
        if (this.isEmpty()) {
            throw new EmptyQueueException("Deque vazio");
        }

        T value = this.head.getValue();
        this.head = this.head.getNext();

        if (this.head == null) {
            this.tail = null;
        } else {
            this.head.setPrevious(null);
        }

        return value;
    }

    /**
     * Deleta o ultimo elemento da fila
     * @return T
     * @throws EmptyQueueException
     */
    public T pop() throws EmptyQueueException {
        if (this.isEmpty()) {
            throw new EmptyQueueException("Deque vazio");
        }

        T value = this.tail.getValue();
        this.tail = this.tail.getPrevious();

        if (this.tail == null) {
            this.head = null;
        } else {
            this.tail.setNext(null);
        }

        return value;
    }

    /**
     * Printa os valores do elementos da fila
     * @throws EmptyQueueException
     */
    public void run(Consumer<T> callback) throws EmptyQueueException {
        if (this.isEmpty()) {
            throw new EmptyQueueException("Deque vazio");
        }

        Element pointer = this.head;

        while (pointer != null) {
            callback.accept(pointer.value);
            pointer = pointer.getNext();
        }
    }

    /**
     * Retorna a cabeça
     * @return Element
     */
    public Element getHead() {
        return head;
    }


    /**
     * Define a cabeça
     */
    public void setHead(Element head) {
        this.head = head;
    }

    /**
     * Retorna a cauda
     * @return Element
     */
    public Element getTail() {
        return tail;
    }

    /**
     * Define a cauda
     */
    public void setTail(Element tail) {
        this.tail = tail;
    }



    /**
     * Classe Elemento, responsável por armazenar os dados de cada elemento da lista
     */
    class Element {
        private Element previous;
        private Element next;
        private T value;
    
        public Element(T value) {
            this.value = value;
            this.previous = null;
            this.next = null;
        }
    
        /**
         * Retorna o valor do objeto
         * @return T value
         */
        public T getValue() {
            return this.value;
        }
    
        /**
         * Define o valor de value
         * @param value
         * @return void
         */
        public void setValue(T value) {
            this.value = value;
        }
    
        /**
         * Retorna o ponteiro para o proximo elemento
         * @return Element next
         */
        public Element getNext() {
            return this.next;
        }
    
        /**
         * Define o proximo elemento
         * @param next
         * @return void
         */
        public void setNext(Element next) {
            this.next = next;
        }

        /**
         * Retorna o elemento anterior
         * @return Element previous
         */
        public Element getPrevious() {
            return this.previous;
        }
    
        /**
         * Define o elemento anterior
         * @param previous
         * @return void
         */
        public void setPrevious(Element previous) {
            this.previous = previous;
        }
    }
    
}
