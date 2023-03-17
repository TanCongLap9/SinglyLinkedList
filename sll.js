class Node {
  constructor(data, next = null) { // Tạo node chứa giá trị value
    this.data = data;
    this.next = next;
  }
}
class LinkedList {
  #head = null;
  // #tail = null;
  #initialize(value) { // Tạo danh sách bằng cách gán node vào head
    this.#head /* = this.tail */ = new Node(value);
  }
  #resetHead() { // Làm trống danh sách khi chỉ còn 1 node
    this.#head /* = this.tail */ = null;
  }
  #throwIfEmpty() {
    if (this.#head === null) throw new Error("Linked list is empty");
  }
  * entries() {
    for (let node = this.#head, i = 0; node !== null; node = node.next, i++) yield [i, node];
  }
  * keys() {
    for (let node = this.#head, i = 0; node !== null; node = node.next, i++) yield i;
  }
  * values() {
    for (let node = this.#head; node !== null; node = node.next) yield node;
  }
  // Các hàm truy cập node
  getFirst() {this.#throwIfEmpty(); // Giá trị của node đầu
    return this.#head.data;
  }
  getAt(index) {this.#throwIfEmpty(); // Giá trị của node tại index
    for (const [i, node] of this.entries())
      if (i === index) return node.data;
    throw new RangeError("Index out of bounds");
  }
  getLast() {this.#throwIfEmpty(); // Giá trị của node cuối
    for (const node of this)
      if (node.next === null) return node.data;
    // Nếu có tail, các câu trên có thể viết rút gọn vậy nè:
    // return this.tail.data;
  }
  // Các hàm đi qua các node
  size() { // Kích thước DSLK (số lượng các node trong danh sách)
    let i;
    for (i of this.keys());
    return i + 1;
  }
  traverse() { // Duyệt DSLK
    console.log(this.#head);
    if (this.#head === null) alert("(empty)");
    for (const node of this)
      alert(node.data)
  }
  search(value) { // Tìm giá trị trong DSLK
    for (const [i, node] of this.entries())
      if (node.data === value) return i;
    return -1;
  }
  // Các hàm thêm node
  addFirst(value) { // Thêm node vào đầu DSLK
    if (this.#head === null) {this.#initialize(value); return;}
    this.#head = new Node(value, this.#head);
  }
  addAt(index, value) { // Thêm node vào trước index
                        // Để thêm node vào sau thì tăng index lên 1
    if (index === 0) {this.addFirst(value); return;}
    if (index === this.size()) {this.addLast(value); return;}
    for (const [i, node] of this.entries())
      if (i === index - 1 && node.next !== null) {
        node.next = new Node(value, node.next); return;
      }
    throw new RangeError("Index out of bounds");
  }
  addLast(value) { // Thêm node vào cuối DSLK
    if (this.#head === null) {this.#initialize(value); return;}
    for (const node of this)
      if (node.next === null) {/* this.tail = */ node.next = new Node(value); break;}
    // Nếu có tail, 2 câu trên có thể viết rút gọn vậy nè:
    // this.tail = this.tail.next = new Node(value);
  }
  // Các hàm xoá node
  removeFirst() {this.#throwIfEmpty(); // Xoá node ở đầu DSLK
    if (this.#head.next === null) this.#resetHead();
    const after = this.#head.next;
    this.#head = after;
  }
  removeAt(index) {this.#throwIfEmpty(); // Xoá node ở vị trí n của DSLK
    if (index === 0) {this.removeFirst(); return;}
    if (index === this.size() - 1) {this.removeLast(); return;}
    for (const [i, node] of this.entries())
      if (i === index - 1 && node.next?.next !== null) {
        const after = node.next.next;
        node.next = after;
        return;
      }
    throw new RangeError("Index out of bounds");
  }
  removeLast() {this.#throwIfEmpty(); // Xoá node ở cuối DSLK
    if (this.#head.next === null) this.#resetHead();
    for (const node of this)
      if (node.next.next === null) {
        node.next = null;
        // this.tail = node;
      }
  }
}
LinkedList.prototype[Symbol.iterator] = LinkedList.prototype.values;
var giaTri, viTri, hanhDong, dslk = new LinkedList();
while (true) {
  hanhDong = prompt("Các lệnh:\ngiatridau    giatricuoi    giatritai <vị trí>\nthemdau <giá trị>    themcuoi <giá trị>    themtai <giá trị> <vị trí>\nxoadau    xoacuoi    xoatai <vị trí>\nduyet    kichthuoc    timkiem <giá trị>\nNhập lệnh hoặc nhấn nút [Huỷ bỏ] để thoát.");
  if (hanhDong === null) break;
  switch (hanhDong.split(" ")[0]) {
    case "giatridau": alert("= " + dslk.getFirst()); break;
    case "giatricuoi": alert("= " + dslk.getLast()); break;
    case "giatritai": viTri = Number(hanhDong.split(" ")[1]); alert("= " + dslk.getAt(viTri)); break;
    case "themdau": giaTri = Number(hanhDong.split(" ")[1]); dslk.addFirst(giaTri); break;
    case "themcuoi": giaTri = Number(hanhDong.split(" ")[1]); dslk.addLast(giaTri); break;
    case "themtai": viTri = Number(hanhDong.split(" ")[1]); giaTri = Number(hanhDong.split(" ")[2]); dslk.addAt(viTri, giaTri); break;
    case "xoadau": dslk.removeFirst(); break;
    case "xoacuoi": dslk.removeLast(); break;
    case "xoatai": viTri = Number(hanhDong.split(" ")[1]); dslk.removeAt(viTri); break;
    case "duyet": dslk.traverse(); break;
    case "kichthuoc": alert("= " + dslk.size()); break;
    case "timkiem":
      var giaTri = Number(hanhDong.split(" ")[1]);
      var viTriTimRa = dslk.search(giaTri);
      alert("= " + viTriTimRa + (viTriTimRa != -1 ? " (vị trí tìm ra)" : " (không tìm ra)"));
      break;
    default: alert("??");
  }
}
