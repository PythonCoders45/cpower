// c^ Standard Library - File Module
class File {

    // Writes text to a file
    public bool write(string filepath, string content) {
        return __native_file_write(filepath, content);
    }

    // Reads a file's contents
    public string read(string filepath) {
        return __native_file_read(filepath);
    }

    // Appends text to a file
    public bool append(string filepath, string content) {
        return __native_file_append(filepath, content);
    }

    // Deletes a file
    public bool remove(string filepath) {
        return __native_file_delete(filepath);
    }

    // Checks if file exists
    public bool exists(string filepath) {
        return __native_file_exists(filepath);
    }
}
