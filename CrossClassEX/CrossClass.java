package org.apache.ignite.examples.datagrid;

import org.apache.ignite.binary.BinaryObjectException;
import org.apache.ignite.binary.BinaryReader;
import org.apache.ignite.binary.BinaryWriter;
import org.apache.ignite.binary.Binarylizable;

public class CrossClass implements Binarylizable {
    CrossClass(long id, int idPart){
        this.id = id;
        this.idPart = idPart;
    }
    private long id;

    private int idPart;

    public void readBinary(BinaryReader reader) throws BinaryObjectException {
        id = reader.readLong("id");
        idPart = reader.readInt("idPart");
    }

    public void writeBinary(BinaryWriter writer) throws BinaryObjectException {
        writer.writeLong("id", id);
        writer.writeInt("idPart", idPart);
    }
}
