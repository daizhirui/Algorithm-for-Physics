union paramBox
{
    int     intValue;
    int*    intPtr;
    long    longValue;
    long*   longPtr;
    float   floatValue;
    float*  floatPtr;
    double  doubleValue;
    double* doublePtr;
    char    charValue;
    char*   charPtr;
    string* stringPtr;
};
int main()
{
    paramBox box;
    box.charValue = 'A';
    char c = box.charValue; // it's OK!
    cout << c << endl;
    cout << sizeof(box) << endl;    // 8
    box.intValue = 1;
    char d = box.charValue; // It's empty!
    int num = box.intValue; // It's OK!
    cout << d << endl;
    cout << num << endl;
    cout << sizeof(box) << endl;    // 8
    return 0;
}
