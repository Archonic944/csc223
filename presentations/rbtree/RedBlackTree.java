import java.util.Comparator;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Stack;
import java.util.TreeSet;

public class RedBlackTree<T extends Comparable<T>> implements Iterable<T> {
    Comparator<T> comparator = Comparator.naturalOrder();

    class RBNode {
        RBNode left;
        RBNode right;
        RBNode parent;

        T data;
        boolean black;

        public RBNode(T data, boolean black){
            this.data = data;
            this.black = black;
        }

        RBNode grandparent(){
            if(parent == null) return null;
            return parent.parent;
        }

        RBNode sibling(){
            if(parent == null) return null;
            return (parent.left == this) ? parent.right : parent.left;
        }

        RBNode uncle(){
            RBNode g = grandparent();
            if(g == null) return null;
            if(parent == g.left) return g.right;
            else return g.left;
        }
    }

    RBNode root;

    @Override
    public Iterator<T> iterator() {
        return new Iterator<T>() {
            Stack<RBNode> stack = new Stack<>();
            {
                if(root != null){
                    stack.add(root);
                    RBNode next = root.left;
                    while(next != null){
                        stack.add(next);
                        next = next.left;
                    }
                }
            }

            @Override
            public boolean hasNext() {
                return !stack.isEmpty();
            }

            @Override
            public T next() {
                RBNode node = stack.pop();
                T result = node.data;
                RBNode next = node.right;
                while(next != null){
                    stack.add(next);
                    next = next.left;
                }
                return result;
            }
            
        };
    }

    void rotateLeft(RBNode x){
        RBNode y = x.right;
        // right's left subtree becomes my right child
        x.right = y.left;
        if(y.left != null){
            y.left.parent = x;
        }

        // connect right to the rest of the tree (x's old parent)
        y.parent = x.parent;
        
        if(x.parent == null){
            root = y;
        }else if(x == x.parent.left){
            x.parent.left = y;
        }else if(x == x.parent.right){
            x.parent.right = y;
        }

        // set y's left subtree to x 
        y.left = x;
        x.parent = y;
    }

    void rotateRight(RBNode x){
        RBNode y = x.left;
        // left's right subtree becomes my left child
        x.left = y.right;
        if(y.right != null){
            y.right.parent = x;
        }

        // connect left to the rest of the tree
        y.parent = x.parent;

        if(x.parent == null){
            root = y;
        }else if(x == x.parent.right){
            x.parent.right = y;
        }else{
            x.parent.left = y;
        }

        // set y's right subtree to x
        y.right = x;
        x.parent = y;
    }

    void case1I(RBNode n){
        if(n.parent == null){
            n.black = true;
        }else{
            case2I(n);
        }
    }

    void case2I(RBNode n){
        if(n.parent.black) return;
        else case3I(n);
    }

    void case3I(RBNode n){
        RBNode u = n.uncle();
        RBNode g = n.grandparent();
        if(u != null && !u.black){
            n.parent.black = true;
            u.black = true;
            g.black = false;
            case1I(g);
        }else{
            case4I(n);
        }
    }

    void case4I(RBNode n){
        RBNode g = n.grandparent();
        if((n == n.parent.right) && (n.parent == g.left)){
            rotateLeft(n.parent);
            n = n.left;
        }else if((n == n.parent.left) && (n.parent == g.right)){
            rotateRight(n.parent);
            n = n.right;
        }
        case5I(n);
    }

    void case5I(RBNode n){
        RBNode g = n.grandparent();
        if((n == n.parent.left) && (n.parent == g.left)){
            rotateRight(g);
        }else if((n == n.parent.right) && (n.parent == g.right)){
            rotateLeft(g);
        }
        n.parent.black = true;
        g.black = false;
    }

    public boolean addNode(T data){
        RBNode n = bstInsert(data);
        if(n == null) return false;
        case1I(n);
        return true;
    }

    RBNode bstInsert(T data){
        if(root == null){
            return (root = new RBNode(data, false)); // root assignment handled by case1
        }

        RBNode current = root;
        while(current != null){
            int c = data.compareTo(current.data);
            if(c == 0) return null;
            RBNode next;
            if(c > 0){
                next = current.right;
                if(next == null){
                    current.right = new RBNode(data, false);
                    current.right.parent = current;
                    return current.right;
                }
            }else{
                next = current.left;
                if(next == null){
                    current.left = new RBNode(data, false);
                    current.left.parent = current;
                    return current.left;
                }
            }
            current = next;
        }

        throw new RuntimeException("what...??");
    }

    public RedBlackTree(Comparator<T> c){
        comparator = c;
    }



    public RedBlackTree(){}

    public static void main(String[] args) {
        // RedBlackTree<Integer> rbTree = new RedBlackTree<>();
        // rbTree.root = rbTree.new RBNode(5, false);
        // RedBlackTree<Integer>.RBNode next = rbTree.new RBNode(4, false);
        // rbTree.root.left = next;
        // RedBlackTree<Integer>.RBNode next2 = rbTree.new RBNode(2, false);
        // next.left = next2;
        // RedBlackTree<Integer>.RBNode next3 = rbTree.new RBNode(1, false);
        // next2.left = next3;
        // RedBlackTree<Integer>.RBNode next4 = rbTree.new RBNode(3, false);
        // next2.right = next4;
        // RedBlackTree<Integer>.RBNode next5 = rbTree.new RBNode(6, false);
        // rbTree.root.right = next5;
        // for(int i : rbTree){
        //     System.out.println(i);
        // }
        Scanner s = new Scanner(System.in);
        RedBlackTree<Integer> tree = new RedBlackTree<>();
        for(int i = 1; i<=10; i++){
            tree.addNode(i);
            for(int j : tree){
                System.out.print(j + " ");
            }
            System.out.println();
            s.nextLine();
        }
    }
}
