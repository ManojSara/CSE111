// $Id: file_sys.cpp,v 1.13 2022-01-26 16:10:48-08 - - $

#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std;

#include "debug.h"
#include "file_sys.h"

size_t inode::next_inode_nr {1};

ostream& operator<< (ostream& out, file_type type) {
   switch (type) {
      case file_type::PLAIN_TYPE: out << "PLAIN_TYPE"; break;
      case file_type::DIRECTORY_TYPE: out << "DIRECTORY_TYPE"; break;
      default: assert (false);
   };
   return out;
}

inode_state::inode_state() {
   root = cwd = make_shared<inode> (file_type::DIRECTORY_TYPE);
   directory_entries& dirents = root->get_dirents();
   dirents.insert (dirent_type (".", root));
   dirents.insert (dirent_type ("..", root));
   DEBUGF ('i', "root = " << root << ", cwd = " << cwd
           << ", prompt = \"" << prompt() << "\""
           << ", file_type = " << root->contents->file_type());
}

const string& inode_state::prompt() const { return prompt_; }

void inode_state::prompt (const string& new_prompt) {
   prompt_ = new_prompt;
}

ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}

inode::inode(file_type type): inode_nr (next_inode_nr++) {
   switch (type) {
      case file_type::PLAIN_TYPE:
           contents = make_shared<plain_file>();
           break;
      case file_type::DIRECTORY_TYPE:
           contents = make_shared<directory>();
           break;
      default: assert (false);
   }
   DEBUGF ('i', "inode " << inode_nr << ", type = " << type);
}

size_t inode::get_inode_nr() const {
   DEBUGF ('i', "inode = " << inode_nr);
   return inode_nr;
}

directory_entries& inode::get_dirents() {
   return contents->get_dirents();
}



file_error::file_error (const string& what):
            runtime_error (what) {
}

const wordvec& base_file::readfile() const {
   throw file_error ("is a " + file_type());
}

void base_file::writefile (const wordvec&) {
   throw file_error ("is a " + file_type());
}

void base_file::remove (const string&) {
   throw file_error ("is a " + file_type());
}

inode_ptr base_file::mkdir (const string&) {
   throw file_error ("is a " + file_type());
}

inode_ptr base_file::mkfile (const string&) {
   throw file_error ("is a " + file_type());
}

directory_entries& base_file::get_dirents() {
   throw file_error ("is a " + file_type());
}



size_t plain_file::size() const {
   size_t size {0};
   for (unsigned long i = 0; i < data.size(); i++)
      size += data[i].size();
   DEBUGF ('i', "size = " << size);
   return size;
}

const wordvec& plain_file::readfile() const {
   DEBUGF ('i', data);
   return data;
}

void plain_file::writefile (const wordvec& words) {
   data = words;
   DEBUGF ('i', words);
}

size_t directory::size() const {
   size_t size {0};
   size = dirents.size();
   DEBUGF ('i', "size = " << size);
   return size;
}

void directory::remove (const string& filename) {
   DEBUGF ('i', filename);
}

inode_ptr directory::mkdir (const string& dirname) {
   DEBUGF ('i', dirname);
   return nullptr;
}

inode_ptr directory::mkfile (const string& filename) {
   DEBUGF ('i', filename);
   return nullptr;
}

directory_entries& directory::get_dirents() {
   return dirents;
}

