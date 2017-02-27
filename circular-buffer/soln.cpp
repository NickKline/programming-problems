#include <vector>
// basker at the end. 
// dist file sysytem, and other people build on top
#include <iostream>
using namespace std;

// serial solution
class CircularBufferInts {
private:
  int maxlen;
  int curlen;
  int rpos, wpos;
  vector<int> data;
  bool notfull() { return (curlen < maxlen); }
  bool notempty() { return (curlen > 0); }

public:
  CircularBufferInts(int _len) {
    maxlen = _len;
    data.resize(maxlen);
    curlen = 0;
    rpos = wpos = 0;
  }
  
  void read(bool& success, int& val) {
    //    cout << "trying to read" << endl;
    if (notempty()) {
      curlen--;
      val = data[rpos++];
      if (rpos > maxlen)
	rpos = 0;
      success = true;
      //      cout << "reading worked "<< val << endl;
    } else {
      //      cout << "reading failed "<< endl;
      success = false;
    }
  }

  void write(bool& success, int& val) {
    //    cout << "writing " << val << endl;
    if (notfull()) {
      curlen++;
      data[wpos] = val;
      wpos++;
      if (wpos > maxlen)
	wpos = 0;
      success = true;
      //      cout << "writing worked "<< val << endl;
    } else {
      success = false;
      //    cout << "writing failed "<< val << endl;
    }
  }
  void dump() {
    printf("maxlen %d cur len %d writing at %d reading at %d\n",
	   maxlen, curlen, wpos, rpos);
  }
};

#define assert(worked)			\
{  \
  if (!worked) { \
    cerr << "failed check at line " << __FILE__ << " in " << __LINE__ << endl;	\
    exit(-1); \
  } \
}

int main() {
  
  int size = 10;
  CircularBufferInts cb(size);
  // 10 writes work
  bool worked;
  int val;
  for (int i = 0; i < size; i++) {
    val = i;
    cb.write(worked, val);
    assert(worked);
  }
  // 11th fails
  val = 11;
  cb.write(worked, val);
  assert(!worked);
  
  // now read 10 times.
  for (int i = 0; i < size; i++) {
    cb.read(worked, val);
    assert(worked);
    assert((val == i));
  }
  cb.read(worked, val);
  assert(!worked);
}
