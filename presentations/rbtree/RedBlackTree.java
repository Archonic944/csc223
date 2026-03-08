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

        RBNode successor(){
            RBNode next = right;
            while(next != null){
                if(next.left == null) return next;
                else next = next.left;
            }
            return next;
        }

        RBNode predecessor(){
            RBNode next = left;
            while(next != null){
                if(next.right == null) return next;
                else next = next.right;
            }
            return next;
        }

        boolean isLeaf(){
            return left == null && right == null;
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

    RBNode find(T result){
        RBNode next = root;
        while(next != null){
            int c = result.compareTo(next.data);
            if(c == 0){
                return next;
            }else if(c > 0){
                next = next.right;
            }else{
                next = next.left;
            }
        }
        return null;
    }

    boolean remove(T data){
        RBNode n = find(data);
        if(n == null) return false;
        deleteChild(n);
        return true;
    }


    void deleteChild(RBNode n){
        // is it the root
        if(n == root){
            if(n.isLeaf()){
                root = null;
            }else if(n.left == null){
                root = n.right;
                root.parent = null;
                root.black = true;
            }else if(n.right == null){
                root = n.left;
                root.parent = null;
                root.black = true;
            }else{
                // two children
                RBNode s = n.successor();
                n.data = s.data;
                deleteChild(s);
            }
            return;
        }
        RBNode dnSibling;
        boolean dnBlack;
        boolean dnIsLeft;
        // is it a leaf?
        if(n.isLeaf()){
            dnSibling = n.sibling();
            dnIsLeft = (n.parent.left == n);
            dnBlack = n.black;
            if(n.parent.left == n){
                n.parent.left = null;
            }else if(n.parent.right == n){
                n.parent.right = null;
            }
        }else{
            // does it have an only child?
            RBNode child = null;
            if(n.left == null){
                child = n.right;
            }else if(n.right == null){
                child = n.left;
            }
            if(child != null){
                dnSibling = n.sibling();
                dnIsLeft = (n.parent.left == n);
                dnBlack = n.black;
                replaceNode(n, child);
            }
            else{
                // two children
                RBNode s = n.successor();
                n.data = s.data;
                dnSibling = s.sibling();
                dnIsLeft = (s.parent.left == s);
                dnBlack = s.black;
                replaceNode(s, null);
            }
        }
        if(!dnBlack) return;
        // rebalance the tree
        // case 1: sibling is red
        case1D(dnSibling, dnIsLeft);
    }

    void case1D(RBNode dnSibling, boolean dnIsLeft){
        if(!dnSibling.black){
            dnSibling.black = true;
            dnSibling.parent.black = false;
            if(dnSibling == dnSibling.parent.right){
                rotateLeft(dnSibling.parent);
            }else{
                rotateRight(dnSibling.parent);
            }
            case2D(dnIsLeft ? dnSibling.left.right : dnSibling.right.left, dnIsLeft);
        }else{
            case2D(dnSibling, dnIsLeft);
        }
    }

    void case2D(RBNode dnSibling, boolean dnIsLeft){
        if(dnSibling.black &&
            (dnSibling.left == null || dnSibling.left.black) &&
               (dnSibling.right == null || dnSibling.right.black)
        ){
            dnSibling.black = false;
            if(!dnSibling.parent.black){
                dnSibling.parent.black = true;
            }else{
                case1D(dnSibling.parent.sibling(), dnSibling.parent.left == dnSibling.parent);
            }
        }else{
            case3D(dnSibling, dnIsLeft);
        }
    }

    void case3D(RBNode dnSibling, boolean dnIsLeft){
        RBNode nearChild = (dnIsLeft ? dnSibling.left : dnSibling.right);
        RBNode farChild = dnIsLeft ? dnSibling.right : dnSibling.left;
        if(nearChild != null && farChild != null && !nearChild.black && farChild.black){
            nearChild.black = true;
            dnSibling.black = false;
            if(dnIsLeft){
                rotateRight(dnSibling);
            }else{
                rotateLeft(dnSibling);
            }
            case4D(dnSibling.parent, dnIsLeft);
        }
        case4D(dnSibling, dnIsLeft);
    }

    void case4D(RBNode dnSibling, boolean dnIsLeft){
        if(dnSibling.black){
            RBNode farChild = dnIsLeft ? dnSibling.right : dnSibling.left;
            if(farChild != null && !farChild.black){
                dnSibling.black = dnSibling.parent.black;
                dnSibling.parent.black = true;
                farChild.black = true;
                if(dnIsLeft){
                    rotateLeft(dnSibling.parent);
                }else{
                    rotateRight(dnSibling.parent);
                }
            }
        }
    }

    /**
     * Replaces n with m
     * @param n replacee, to be effectively removed from the tree
     * @param m replacer, to fill n's place
     */

    void replaceNode(RBNode n, RBNode m){
        if(n.parent.left == n){
            n.parent.left = m;
        }else{
            n.parent.right = m;
        }
        if(m != null) m.parent = n.parent;
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
        while(true){
            System.out.println("Main menu\n1. Insert\n2. Remove\n3. Print");
            int c = s.nextInt();
            if(c == 1){
                System.out.println("Enter value to insert:");
                int v = s.nextInt();
                tree.addNode(v);
            }else if(c == 2){
                System.out.println("Enter value to remove:");
                int v = s.nextInt();
                tree.remove(v);
            }else if(c == 3){
                for(int i : tree){
                    System.out.print(i + " ");
                }
                System.out.println();
            }
        }
    }
}
