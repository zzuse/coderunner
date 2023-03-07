export default class MinHeap {
    public length: number;
    private data: number[];



    constructor() {
        this.data = [];
        this.length = 0;
    }

    insert(value: number): void {

    }
    delete(): number {

    }

    private parent(idx: number): number {
        return Math.floor((idx - 1) / 2);   
    }

    private heapifyDown(idx: number): void{
        if(idx >= this.length) {
            return;
        }
        const lIdx = this.leftChild(idx);
        const rIdx = this.rightChild(idx);
        if(idx >= this.length || lIdx >= this.length) {
            return
        }
        const lV = this.data[lIdx];
        const rV = this.data[rIdx];
        const v = this.data[idx];
        if (lV > rV && v > rV){
            this.data[idx]=rV;
            this.data[rIdx]=v;
            this.heapifyDown(rIdx);
        }
    }

    private heapifyUp(idx: number): void {
        if(idx == 0) {
            return;
        }
        const p = this.parent(idx);
        const parentV=this.data[p];
        const v = this.data[idx];
        if (parentV > v) {
            this.data[idx] = parent;
            this.data[p] = v;
            this.heapifyUp(p);
        }
    }

    private leftChild(idx: number): number {
        return idx *2 + 1;
    }
    private rightChild(idx: number): number {
        return idx *2 + 2;
    }
}
