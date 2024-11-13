extern "C"{
    #include "mz.h"
    #include "mz_os.h"
    #include "mz_strm.h"
    #include "mz_strm_buf.h"
    #include "mz_strm_split.h"
    #include "mz_zip.h"
    #include "mz_zip_rw.h"
}
#include <vector>
#include <string>

#ifdef DEBUG
#include "stdio.h"
#else
#define printf(...)
#endif

#ifdef WIN32
#define PATH_OFFSET_CORRECTION 1
#else
#define PATH_OFFSET_CORRECTION 0
#endif

// Gryab: basically copy-paste from the minizip.c file
int32_t minizip_list(const std::string &path, std::vector<std::string> &filesInfo) {
    //uint32_t ratio = 0;
    //struct tm tmu_date;
    //const char *method = NULL;
    //char crypt = ' ';
    mz_zip_file *file_info = NULL;
    int32_t err = MZ_OK;
    void *reader = NULL;

    filesInfo.clear();

    reader = mz_zip_reader_create();
    if (!reader)
        return MZ_MEM_ERROR;

    err = mz_zip_reader_open_file(reader, path.substr(PATH_OFFSET_CORRECTION).c_str());
    if (err != MZ_OK) {
        printf("Error %" PRId32 " opening archive %s\n", err, path.substr(PATH_OFFSET_CORRECTION).c_str());
        mz_zip_reader_delete(&reader);
        return err;
    }

    err = mz_zip_reader_goto_first_entry(reader);

    if (err != MZ_OK && err != MZ_END_OF_LIST) {
        printf("Error %" PRId32 " going to first entry in archive\n", err);
        mz_zip_reader_delete(&reader);
        return err;
    }

    /* Enumerate all entries in the archive */
    while (err == MZ_OK) {
        err = mz_zip_reader_entry_get_info(reader, &file_info);

        if (err != MZ_OK) {
            printf("Error %" PRId32 " getting entry info in archive\n", err);
            break;
        }
/*
        ratio = 0;
        if (file_info->uncompressed_size > 0)
            ratio = (uint32_t)((file_info->compressed_size * 100) / file_info->uncompressed_size);

        //Display a '*' if the file is encrypted
        if (file_info->flag & MZ_ZIP_FLAG_ENCRYPTED)
            crypt = '*';
        else
            crypt = ' ';

        method = mz_zip_get_compression_method_string(file_info->compression_method);
        mz_zip_time_t_to_tm(file_info->modified_date, &tmu_date);
*/

        // Gryab: marked-out output store

        filesInfo.push_back(std::string(file_info->filename));
        filesInfo.push_back(std::to_string(file_info->uncompressed_size));
        filesInfo.push_back(std::to_string(file_info->compressed_size));
        // ------------------------------

        err = mz_zip_reader_goto_next_entry(reader);

        if (err != MZ_OK && err != MZ_END_OF_LIST) {
            printf("Error %" PRId32 " going to next entry in archive\n", err);
            break;
        }
    }

    mz_zip_reader_delete(&reader);

    if (err == MZ_END_OF_LIST)
        return MZ_OK;

    return err;
}
