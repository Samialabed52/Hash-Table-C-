#include <iostream>

using namespace std;

const int TABLE_SIZE = 17;

int ref = TABLE_SIZE;

bool is_prime(int val)
{
    int ref{0};
    
    if(val == 2 || val == 3)
        return true;
    else
        {
            for(int i{2}; i < val; i++)
            {
                if(val % i == 0)
                    ref++;
            }
            if(ref >= 1)
                return false;
            else
                return true;
        }
}

int next_prime(int val)
{
    val *= 2;
    if(val % 2 == 0)
        val++;
    while(!is_prime(val))
        val += 2;
    return val;
}

class HashEntry
{
    friend class HashMap;
private:
    int key;
    int value;
public:
    void giveKey(int val)
    {
        this->key = val % TABLE_SIZE;
        this->value = val;        
    }
    int updateKey(int key)
    {
      this->key = key;
    }
    int getKey()
    {
        return this->key;
    }
    int getValue(int key)
    {
        cout << "Value " << key << " is in the cell " << this->key << endl;
        return this->value;
    }
};
 
class HashMap 
{
private:
      HashEntry **table;
public:
      HashMap() 
      {
            table = new HashEntry *[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                  table[i] = NULL;
      }
 
      int get(int key) 
      {
            int hash = (key % TABLE_SIZE); 
            while (table[hash] != NULL && table[hash]->getKey() != key) 
                  hash = (hash + 1) % TABLE_SIZE; 
            if (table[hash] == NULL) 
                  return -1;
            else 
                  return table[hash]->getValue(hash);
      }
 
      void insert(int value) 
      {
          //int hash = (value % TABLE_SIZE);
          HashEntry *entry = new HashEntry();
          entry->giveKey(value);
          cout << "Value " << entry->value << " is in the cell " << entry->key << endl;
          int current_size{0};
          
          if(current_size > TABLE_SIZE/2)
          {
              rehash();
              
          }
          
          while (table[entry->key] != NULL)
          {
              int hash = (entry->key + 1) % TABLE_SIZE;
              entry->updateKey(hash);
              
          }
          if(table[entry->key] == NULL)
          {
              table[entry->key] = entry;
              current_size++;
          }
          if(table[entry->key]->getKey() == value)
          {
              cout << "[WARNING] Key exists" << endl;
          }
      }     
 
    void rehash()
    {
        int value;
        if(ref == TABLE_SIZE)
        {
            value = next_prime(TABLE_SIZE);
        }
        else
        {
            value = next_prime(ref);
        }
        HashEntry **newTable;
        newTable = new HashEntry *[value];
        for(auto i {0}; i < ref; i++)
        {
            newTable[i] = table[i];
        }
        ref = value;
        table = newTable;
    }
 
      ~HashMap() 
      {
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL)
                        delete table[i];
            delete[] table;
      }
};

int main()
{
    HashMap table1;
    table1.insert(121);
    return 0;
}