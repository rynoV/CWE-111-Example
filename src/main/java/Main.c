#include <stdio.h>
#include "org_example_Main.h"

// This is the implementation of the native writeToAccountingFile declaration from Main.java
JNIEXPORT void JNICALL Java_org_example_Main_writeToAccountingFile(JNIEnv *env, jobject obj)
{
    jclass cls = (*env)->GetObjectClass(env, obj);

    jfieldID compensationFieldId = (*env)->GetFieldID(env, cls, "compensation", "I");
    // This is where we start to read from the JNI the HR system name which John managed to change.
    jfieldID nameFieldId = (*env)->GetFieldID(env, cls, "name", "Ljava/lang/String;");

    jint jCompensation = (*env)->GetIntField(env, obj, compensationFieldId);

    jobject nameObject = (*env)->GetObjectField(env, obj, nameFieldId);
    const char *jName;
    jName = (*env)->GetStringUTFChars(env, nameObject, NULL);

    FILE *file = fopen("./accounting-compensation.ssv", "a");
    // John managed to change his name to be 7 characters long, so with strcpy,
    // the last character of John's name will be written into compensation. A
    // possible solution would be to use strncpy instead of strcpy.
    int compensation = jCompensation;
    char name[6];
    strcpy(name, jName);

    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(file, "%s  %d\n", name, compensation);
//    printf("%s  %d\n", name, compensation);
    fclose(file);
    return;
}
