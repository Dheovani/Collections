package com.collections;

public class UnexistentElementException extends Exception {
    public UnexistentElementException(String msg) {
        super(msg);
    }

    @Override
    public void printStackTrace() {
        super.printStackTrace();
    }
}
