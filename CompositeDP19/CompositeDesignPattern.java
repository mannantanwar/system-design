package CompositeDP19;

import java.util.ArrayList;
import java.util.List;


/**
 * FileSystemItem
*/ 
interface FileSystemItem {
    void openAll(int indent);
    void ls( int indent);
    FileSystemItem cd(String name);
    int getSize();
    String getName();
    boolean isFolder();
}

class File implements FileSystemItem{
    private String name ;
    private int size;

    public File(String name , int size){
        this.name =name ;
        this.size= size;
    }
    
    @Override
    public void openAll(int indent){
        String indentSpaces = " ".repeat(indent);
        System.out.println(indentSpaces + name);
    }
    @Override
    public void ls(int indent){
        String indentSpaces = " ".repeat(indent);
        System.out.println(indentSpaces + name);
    }
    @Override
    public FileSystemItem cd(String name) {
        System.out.println("already inside a file cannot go more in ");
        return null;
    }
    @Override
    public int getSize(){
        return this.size;
    }
    @Override
    public String getName(){
        return this.name;
    }
    @Override
    public boolean isFolder(){
        return false;
    }
}

class Folder implements FileSystemItem{
    private String name;
    private List<FileSystemItem>children;
    
    
    public Folder(String name ){
        this.name = name ;
        this.children = new ArrayList<>();
    }

    public void add(FileSystemItem item){
        children.add(item);
    }
    
    @Override
    public void openAll(int indent){
        String indentSpaces = " ".repeat(indent);
        for (FileSystemItem child: children ){
            child.openAll(indent+4);
        }
        
    }
    @Override
    public void ls(int indent) {
        String indentSpaces = " ".repeat(indent);
        for (FileSystemItem child : children) {
            if (child.isFolder()) {
                System.out.println(indentSpaces + "+ " + child.getName());
            } else {
                System.out.println(indentSpaces + child.getName());
            }
        }
    }
    @Override
    public FileSystemItem cd(String name) {
        for(FileSystemItem item : children){
            if(item.isFolder() && item.getName().equals(name))return item;
        }
        return null;
    }
    @Override
    public int getSize(){
        int total =0;
        for(FileSystemItem item : children){
            total+=item.getSize();
        }
        return total;
    }
    @Override
    public String getName(){
        return this.name;
    }
    @Override
    public boolean isFolder(){
        return true;
    }
}

public class CompositeDesignPattern {
    public static void main(String[] args) {
         // Build file system
        Folder root = new Folder("root");
        root.add(new File("file1.txt", 1));
        root.add(new File("file2.txt", 1));

        Folder docs = new Folder("docs");
        docs.add(new File("resume.pdf", 1));
        docs.add(new File("notes.txt", 1));
        root.add(docs);

        Folder images = new Folder("images");
        images.add(new File("photo.jpg", 1));
        root.add(images);

        root.ls(0);

        docs.ls(0);

        root.openAll(0);

        FileSystemItem cwd = root.cd("docs");
        if (cwd != null) {
            cwd.ls(0);
        } else {
            System.out.println("\nCould not cd into docs\n");
        }

        System.out.println(root.getSize());
    }
}