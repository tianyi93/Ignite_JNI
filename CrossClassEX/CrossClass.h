#pragma once
#include "ignite/binary/binary.h"
namespace ignite
{
    namespace binary
    {
        struct CrossClass {
            CrossClass() {}
            CrossClass(int64_t id, int32_t idPart) {
                this->id = id;
                this->idPart = idPart;
            }
            int64_t id;
            int32_t idPart;
        };
        template<>
        struct BinaryType<CrossClass>
        {
            static int32_t GetTypeId()
            {
                return GetBinaryStringHashCode("CrossClass");
            }

            static void GetTypeName(std::string& name)
            {
                name = "CrossClass";
            }

            static int32_t GetFieldId(const char* name)
            {
                return GetBinaryStringHashCode(name);
            }

            static bool IsNull(const CrossClass& obj)
            {
                return false;
            }

            static void GetNull(CrossClass& dst)
            {
                dst = CrossClass();
            }

            static void Read(BinaryReader& reader, CrossClass& dst)
            {
                dst.id = reader.ReadInt64("id");
                dst.idPart = reader.ReadInt32("idPart");
            }

            static void Write(BinaryWriter& writer, const CrossClass& obj)
            {
                writer.WriteInt64("id", obj.id);
                writer.WriteInt32("idPart", obj.idPart);
            }
        };
    }
}
