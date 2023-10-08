package com.collections;

import java.util.EmptyStackException;

public class DynamicList {

    private Element head;
    private Element tail;
    
    public DynamicList() {
        this.head = null;
        this.tail = null;
    }

    /**
     * Este método é responsável por averiguar se algum elemento já foi adicionado à pilha
     * @return boolean
     */
    public boolean isEmpty() {
        return this.head == null && this.tail == null;
    }

    /**
     * Este método é responsável por adicionar um elemento ao topo da pilha
     * @param Object value
     * @return void
     */
    public void add(Object value) {
        Element element = new Element(value);

        if (isEmpty()) {
            this.head = element;
            this.tail = this.head;
            return;
        }

        this.tail.setPointer(element);
        this.tail = element;
    }

    /**
     * Este método é responsável por eliminar o elemento presente no topo da pilha e retorná-lo como resultado
     * @throws EmptyStackException
     * @return Element top
     */
    public Element delete() throws EmptyStackException {
        if (isEmpty()) {
            throw new EmptyStackException();
        }

        Element element = this.head;

        if (this.head.getPointer() == null) {
            this.tail = null;
        }

        this.head = this.head.getPointer();

        return element;
    }

    /**
     * Este método retorna o topo da pilha
     * @return Element tail
     */
    public Element getTail() {
        return this.tail;
    }

    /**
     * Este método é responsável por percorrer a pilha e retornar os valores dos elementos
     * @return void
     */
    public void run() {
        Element element = this.head;

        do {
            System.out.println(element.getValue());
            element = element.getPointer();
        } while (element != null);
    }

    /**
     * Classe Elemento, responsável por armazenar os dados de cada elemento da lista
     */
    class Element {
        private Object value;
        private Element pointer;
    
        public Element(Object value) {
            this.value = value;
            this.pointer = null;
        }
    
        /**
         * Retorna o valor do objeto
         * @return Object value
         */
        public Object getValue() {
            return this.value;
        }
    
        /**
         * Define o valor de value
         * @param value
         * @return void
         */
        public void setValue(Object value) {
            this.value = value;
        }
    
        /**
         * Retorna o ponteiro para onde o elemento aponta
         * @return Element pointer
         */
        public Element getPointer() {
            return this.pointer;
        }
    
        /**
         * Define o ponteiro para onde o elemento aponta
         * @param pointer
         * @return void
         */
        public void setPointer(Element pointer) {
            this.pointer = pointer;
        }
    }
    
}
