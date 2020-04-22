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
        ArrayList<ArrayList<String>> matrix = new ArrayList<ArrayList<String>>();
        matrix.add(v);
        matrix.add(v);
        new passvecjni().passmatrix(matrix, 2, 2);
    }
    private native void passvec(ArrayList<String> v, int size);
    private native void passmatrix(ArrayList<ArrayList<String>> matrix, int rowsz, int colsz);
}