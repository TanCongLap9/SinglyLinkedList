#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <string>
using namespace std;
template <class T> struct Node {T data; Node* next;};
template <class T> class LLIterator: public iterator<input_iterator_tag, Node<T>> {
  Node<T>* node; size_t index;
public:
  LLIterator(Node<T>* p): node(p), index(0) {}
  Node<T>* get() const {return node;}
  size_t getIndex() const {return index;}
  LLIterator<T>& operator++() {node = node->next; ++index; return *this;}
  LLIterator<T>& operator*() {return *this;}
  bool operator!=(LLIterator<T> rhs) const {return node != rhs.node;}
};
template <class T> class LinkedList {
  Node<T>* head = nullptr /*, * tail = nullptr */;
  void initialize(const T& value) { // Tạo danh sách bằng cách gán node vào head
    head /* = tail */ = new Node<T> {value, nullptr};
  }
  void resetHead() { // Làm trống danh sách khi chỉ còn 1 node
    delete head; head /* = tail */ = nullptr;
  }
  void throwIfEmpty() const {
    if (head == nullptr) throw runtime_error("Linked list is empty");
  }
public:
  LLIterator<T> begin() const {return LLIterator<T>(head);}
  LLIterator<T> end() const {return LLIterator<T>(nullptr);}
  // Các hàm truy cập node
  T& getFirst() const {throwIfEmpty(); // Giá trị của node đầu
    return head->data;
  }
  T& getAt(int index) const {throwIfEmpty(); // Giá trị của node tại index
    LLIterator<T> result = find_if(begin(), end(), [index] (LLIterator<T> iter) -> bool {return iter.getIndex() == index;});
    if (result != end()) return result.get()->data;
    throw out_of_range("Index out of bounds: " + to_string(index));
  }
  T& getLast() const {throwIfEmpty(); // Giá trị của node cuối
    return find_if(begin(), end(), [] (LLIterator<T> iter) -> bool {return iter.get()->next == nullptr;}).get()->data;
    // Nếu có tail, câu trên có thể viết rút gọn vậy nè:
    // return tail->data;
  }
  // Các hàm đi qua các node
  size_t size() const { // Kích thước DSLK (số lượng các node trong danh sách)
    return distance(begin(), end());
  }
  void traverse() const { // Duyệt DSLK
    if (head == nullptr) cout << "(empty)";
    for (LLIterator<T> iter: *this) cout << iter.get()->data << " ";
    cout << "\n";
  }
  int search(const T& value) const { // Tìm giá trị trong DSLK
    LLIterator<T> result = find_if(begin(), end(), [&value] (LLIterator<T> iter) -> bool {return iter.get()->data == value;});
    return result != end() ? result.getIndex() : -1;
  }
  // Các hàm thêm node
  void addFirst(const T& value) { // Thêm node vào đầu DSLK
    if (head == nullptr) {initialize(value); return;}
    head = new Node<T> {value, head};
  }
  void addAt(size_t index, const T& value) {
    /* Thêm node vào trước index
       Để thêm node vào sau thì tăng index lên 1 */
    if (index == 0) {addFirst(value); return;}
    if (index == size()) {addLast(value); return;}
    LLIterator<T> result = find_if(begin(), end(), [index] (LLIterator<T> iter) -> bool {return iter.get()->next != nullptr && iter.getIndex() == index - 1;});
    if (result != end()) {result.get()->next = new Node<T> {value, result.get()->next}; return;}
    throw out_of_range("Index out of bounds: " + to_string(index));
  }
  void addLast(const T& value) { // Thêm node vào cuối DSLK
    if (head == nullptr) {initialize(value); return;}
    find_if(begin(), end(), [] (LLIterator<T> iter) -> bool {return iter.get()->next == nullptr;}).get()->next = new Node<T> {value, nullptr};
    // Nếu có tail, các câu trên được viết rút gọn vậy nè:
    // tail = tail->next = new Node<T> {value};
  }
  // Các hàm xoá node
  void removeFirst() {throwIfEmpty(); // Xoá node ở đầu DSLK
    if (head->next == nullptr) {resetHead(); return;}
    Node<T>* after = head->next;
    delete head;
    head = after;
  }
  void removeAt(int index) {throwIfEmpty(); // Xoá node ở vị trí n của DSLK
    if (index == 0) {removeFirst(); return;}
    if (index == size() - 1) {removeLast(); return;}
    LLIterator<T> result = find_if(begin(), end(), [index] (LLIterator<T> iter) -> bool {return iter.get()->next != nullptr && iter.get()->next->next != nullptr && iter.getIndex() == index - 1;});
    if (result != end()) {
      Node<T>* after = result.get()->next->next;
      delete result.get()->next;
      result.get()->next = after;
      return;
    }
    throw out_of_range("Index out of bounds: " + to_string(index));
  }
  void removeLast() {throwIfEmpty(); // Xoá node ở cuối DSLK
    if (head->next == nullptr) {resetHead(); return;}
    LLIterator<T> result = find_if(begin(), end(), [] (LLIterator<T> iter) -> bool {return iter.get()->next->next == nullptr;});
    delete result.get()->next;
    result.get()->next = nullptr;
    // tail = result.get();
  }
};
LinkedList<int> dslk; int giaTri, viTri; string hanhDong;
int main(int argc, char* argv[]) {
  cout << "Cac lenh:\ngiatridau    giatricuoi    giatritai <vi tri>\nthemdau <gia tri>    themcuoi <gia tri>    themtai <vi tri> <gia tri>\nxoadau    xoacuoi    xoatai <vi tri>\nduyet    kichthuoc    timkiem <gia tri>\nthoat\nNhap lenh va nhan Enter.\n";
  while (true) {
    cout << "> "; cin >> hanhDong;
    if (hanhDong == "giatridau") {cout << "= " << dslk.getFirst() << "\n";}
    else if (hanhDong == "giatricuoi") {cout << "= " << dslk.getLast() << "\n";}
    else if (hanhDong == "giatritai") {cin >> viTri; cout << "= " << dslk.getAt(viTri) << "\n";}
    else if (hanhDong == "themdau") {cin >> giaTri; dslk.addFirst(giaTri);}
    else if (hanhDong == "themcuoi") {cin >> giaTri; dslk.addLast(giaTri);}
    else if (hanhDong == "themtai") {cin >> viTri >> giaTri; dslk.addAt(viTri, giaTri);}
    else if (hanhDong == "xoadau") dslk.removeFirst();
    else if (hanhDong == "xoacuoi") dslk.removeLast();
    else if (hanhDong == "xoatai") {cin >> viTri; dslk.removeAt(viTri);}
    else if (hanhDong == "duyet") dslk.traverse();
    else if (hanhDong == "kichthuoc") {cout << "= " << dslk.size() << "\n";}
    else if (hanhDong == "timkiem") {
      cin >> giaTri;
      int viTriTimRa = dslk.search(giaTri);
      cout << "= " << viTriTimRa;
      cout << (viTriTimRa != -1 ? " (vi tri tim ra)" : " (khong tim ra)") << "\n";
    }
    else if (hanhDong == "thoat") break;
    else cout << "??\n";
  }
}
