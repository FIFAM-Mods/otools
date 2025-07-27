#include "main.h"
#include "message.h"

void align_file(path const &out, path const &in) {
    unsigned int pad = options().pad;
    if (pad != 0) {
        FILE *f = _wfopen(in.c_str(), L"rb");
        if (f) {
            fseek(f, 0, SEEK_END);
            unsigned int fsize = ftell(f);
            if (fsize < pad) {
                fseek(f, 0, SEEK_SET);
                vector<unsigned char> fdata(pad, 0);
                fread(fdata.data(), fsize, 1, f);
                fclose(f);
                auto dst = out;
                dst.replace_filename(wstring(out.stem().c_str()) + in.extension().c_str());
                FILE *o = _wfopen(dst.c_str(), L"wb");
                if (o) {
                    fwrite(fdata.data(), fdata.size(), 1, o);
                    fclose(o);
                }
            }
            else {
                InfoMessage(Format("File \"%s\" size (%d bytes) is greater than padding size (%d bytes)",
                    in.filename().string().c_str(), fsize, pad));
            }
        }
    }
}
