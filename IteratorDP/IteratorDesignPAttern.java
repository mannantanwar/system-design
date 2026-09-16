package IteratorDP;

interface Iterator <T>{
    boolean hasNext();
    T next();
}

interface Iterable<T>{
    Iterator<T> getIterator();
}

class LinkedList implements Iterable<LinkedList>{
    LinkedList next;
    Integer value;
    @Override
    public Iterator<LinkedList>getIterator(){
        return new LinkedListIterator(this);
    }
    public LinkedList getNext(){
        return next;
    }

}
class BinaryTree implements Iterable<BinaryTree>{
    BinaryTree left;
    BinaryTree right ;
    Integer value;

    @Override 
    public Iterator<BinaryTree>getIterator(){
        return new BinaryTreeIterator(this);
    }

}
// now the concrete implementation of the interator 
class LinkedListIterator implements Iterator<LinkedList>{
    private LinkedList head;
    
    public LinkedListIterator(LinkedList curr){
        head= curr;
    }
    @Override
    // +dikkat ye aarh ha i ki m jab linked list ki concrete class me getiterator likhunga to is class ka object emekro return hojyga
    // but m us object par has next jab call krunga 
    public boolean hasNext(){
        if(head.next!=null)return true;
        return false;
    }
    @Override 
    public LinkedList next(){
        LinkedList temp = head;
        head = head.next;
        return temp.next;
    }
}

class BinaryTreeIterator implements Iterator<BinaryTree>{
    private BinaryTree curr;
    BinaryTreeIterator(BinaryTree curr){
        this.curr= curr;
    }
    @Override 
    public boolean hasNext(){
        // now the thing is iske next me return kya kru ??check left and check right ?
        if(curr.left !=null || curr.right!=null)return true;
        return false;
    }
    @Override 
    public BinaryTree next(){
        if(curr.left == null && curr.right !=null)return curr.right;
        if(curr.right== null && curr.left!=null)return curr.left;
        return null;
    }
}
public class IteratorDesignPAttern {
    
}
