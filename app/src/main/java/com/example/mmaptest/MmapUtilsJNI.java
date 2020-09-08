package com.example.mmaptest;

public class MmapUtilsJNI {
    static {
        System.loadLibrary("mmap-utils");
    }
    public native String printString(String str);
    public native void init(String filePath);
    public native void setPeople(String name, int age);
    public native String getPeople(int index);
    public native void close();
}
