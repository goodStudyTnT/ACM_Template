bitset<8> foo ("10011011");  
    cout << foo.count() << endl;//5（count函数用来求bitset中1的位数，foo中共有5个１  
    cout << foo.size() << endl;//8（size函数用来求bitset的大小，一共有8位  
    cout << foo.test(0) << endl;//true（test函数用来查下标处的元素是0还是１，并返回false或true，此处foo[0]为１，返回true  
    cout << foo.test(2) << endl;//false（同理，foo[2]为0，返回false  
    cout << foo.any() << endl;//true（any函数检查bitset中是否有１  
    cout << foo.none() << endl;//false（none函数检查bitset中是否没有１  
    cout << foo.all() << endl;//false（all函数检查bitset中是全部为１  
    cout<<foo.set()<<endl;//置为1  
cout<<foo.reset()<<endl;//置为0  
