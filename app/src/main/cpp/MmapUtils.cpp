//
// Created by hopelin on 2020/9/7.
//
#include <string>
#include <jni.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
//#include "com_example_mmaptest_MmapUtilsJNI.h"

extern "C"
JNIEXPORT jstring JNICALL Java_com_example_mmaptest_MmapUtilsJNI_printString
        (JNIEnv *env, jobject, jstring str) {
    const char *chars = env->GetStringUTFChars(str, 0);
    printf("%s! \n",chars);

    std::string strOld = chars;
    std::string strNew = "你输入的是:"+strOld;
    return env->NewStringUTF(strNew.c_str());
}

typedef struct {
    char name[4];
    int age;
}People;

static int fd;
static int currentPeopleNum;
static void *mmapHeadPtr;

void openFile(const char *filePath) {
    if(access(filePath, F_OK) == 0) {
        fd = open(filePath, O_RDWR);
    }else{
        fd = open(filePath, O_RDWR|O_CREAT, 0777);
        if(fd>=0) {
            lseek(fd, sizeof(People)*5-1,SEEK_SET);
            write(fd, "", 1);
        }
    }
    if(fd>=0) {
        mmapHeadPtr = mmap(NULL, sizeof(People) * 10, PROT_READ | PROT_WRITE,
                                         MAP_SHARED, fd, 0);
        close(fd);
    }
    currentPeopleNum = 0;
}

void setPeople(const char *name, int age) {
    if(mmapHeadPtr!=nullptr) {
        People *people = (People *)mmapHeadPtr;
        memcpy((*(people+currentPeopleNum)).name, name, sizeof(char[4]));
        (*(people+currentPeopleNum)).age = age;
        currentPeopleNum++;
    }
}

People* getPeople(int index) {
    if(mmapHeadPtr!=nullptr) {
        People *people = (People *)mmapHeadPtr;
        people = people+index;
        return people;
    }
}

void close() {
    if(mmapHeadPtr!=nullptr) {
        munmap(mmapHeadPtr, sizeof(People) * 10);
    }
}



extern "C"
JNIEXPORT void JNICALL
Java_com_example_mmaptest_MmapUtilsJNI_init(JNIEnv *env, jobject thiz, jstring file_path) {
    const char *chars = env->GetStringUTFChars(file_path, 0);
    openFile(chars);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_mmaptest_MmapUtilsJNI_setPeople(JNIEnv *env, jobject thiz, jstring name,
                                                 jint age) {
    const char *nameStr = env->GetStringUTFChars(name, 0);
    setPeople(nameStr, age);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_mmaptest_MmapUtilsJNI_getPeople(JNIEnv *env, jobject thiz, jint index) {
    People *people = getPeople(index);
    std::string name = people->name;
    std::string strNew = "查询people name="+name+" age="+std::to_string(people->age);
    return env->NewStringUTF(strNew.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_mmaptest_MmapUtilsJNI_close(JNIEnv *env, jobject thiz) {
    close();
}