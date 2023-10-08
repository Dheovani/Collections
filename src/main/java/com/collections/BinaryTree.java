package com.collections;

import java.util.function.Consumer;

public class BinaryTree<T> {

    class Element {
        private Element father;
        private Element rightChild;
        private Element leftChild;
        private T value;

        private Element(T value) {
            this.value = value;
        }

        public Element getFather() {
            return father;
        }

        public void setFather(Element father) {
            this.father = father;
        }

        public Element getRightChild() {
            return rightChild;
        }

        public void setRightChild(Element rightChild) {
            this.rightChild = rightChild;
        }

        public Element getLeftChild() {
            return leftChild;
        }

        public void setLeftChild(Element leftChild) {
            this.leftChild = leftChild;
        }

        public T getValue() {
            return value;
        }

        public void setValue(T value) {
            this.value = value;
        }
    }

    private Element root;
    private Object list[];
    private int layer = 1;

    public boolean isEmpty() {
        return this.root == null;
    }

    /**
     * Adiciona um elemento à fila e retorna o novo elemento
     * @param elementFather
     * @param elementPosition
     * @param value
     * @return
     */
    public Element addElement(Element elementFather, T value) {
        final Element element = new Element(value);
        element.father = elementFather;

        if (this.isEmpty() || elementFather == null) {
            this.root = element;
        } else if (elementFather.leftChild == null) {
            this.layer += 1;
            elementFather.leftChild = element;
        } else {
            elementFather.rightChild = element;
        }

        return element;
    }

    /**
     * Deleta um elemento da fila
     * @param element
     * @param delRoot
     */
    public void deleteElement(Element element, Element delRoot) {
        if (this.isEmpty() || element == null) {
            return;
        }

        if (delRoot == null && this.root.equals(element)) {
            this.root = null;
        } else {
            this.deleteElement(element, this.root.leftChild);
            this.deleteElement(element, this.root.rightChild);
        }
    }

    /**
     * Define o tamanho do array
     * @param val
     * @return
     */
    private int getListSize(int val) {
        int i, j = 1;
        for (i = 1; i < val; i ++) {
            j *= 2;
        }

        return j;
    }

    /**
     * Preenche o array com os elementos da árvore
     * @param pos
     * @param element
     */
    private void fullFillList(int pos, Element element) {
        this.list[pos] = element;
        int lc = 2 * pos + 1,
            rc = 2 * pos + 2;

        if (element.leftChild != null) {
            this.list[lc] = element.leftChild;
            this.fullFillList(lc, element.leftChild);
        }

        if (element.rightChild != null) {
            this.list[rc] = element.rightChild;
            this.fullFillList(rc, element.rightChild);
        }
    }

    /**
     * Recebe um callback no parâmetro consumer para executar com os valores da lista
     * @param element
     * @param consumer
     */
    @SuppressWarnings("unchecked")
    public void run(Element element, Consumer<T> consumer) {
        if (this.isEmpty() || element == null) {
            System.out.println("A fila está vazia");
            return;
        }

        this.list = new Object[this.getListSize(this.layer)];
        this.list[0] = element;
        this.fullFillList(0, element);

        for (int i = 0; i < this.list.length; i ++) {
            if (this.list[i] != null) {
                Element item = (Element) this.list[i];
                consumer.accept(item.value);
            }
        }
    }

}