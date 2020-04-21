import java.util.ArrayList;
public class passvecjni {
    static {
        System.loadLibrary("passvecjni");
    }
    public static void main(String[] args){
        ArrayList<String> v = new ArrayList<String>();
        v.add(0,"col1");
        v.add(1,"col2");
        new passvecjni().passvec(v, v.size());
    }
    private native void passvec(ArrayList<String> v, int size);
}