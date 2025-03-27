#include <iostream>
#include <array>

template<typename T, size_t BlockSize>
class Deque 
{
private:
    std::array<std::array<T, BlockSize>, 2> blocks;
    size_t size1, size2; 
    struct MemoryBlock
    {
        std::array<T*, BlockSize> addresses; 
        size_t blockCount; 
    };

    MemoryBlock memoryBlock;
public:
    Deque() : size1(0), size2(0)
    {
        memoryBlock.blockCount = 2;
        size_t mid = BlockSize / 2;
        memoryBlock.addresses[mid] = blocks[0].data();
    }

    void addBlockAtFront()
    {
        size_t mid = (BlockSize + blocks.size()-1)/2;
        memoryBlock.addresses[mid] = blocks[0].data();
    }

    void addBlockAtBack()
    {
        size_t mid = (BlockSize + blocks.size()-1)/2;
        memoryBlock.addresses[mid] = blocks[blocks.size()-1].data();
    }

    void push_front(const T& val) 
    {
        if (size1 < BlockSize) 
        {
            for (size_t i = size1; i > 0; --i)
                blocks[0][i] = blocks[0][i - 1];
            blocks[0][0] = val;
            ++size1;
        }
        else 
        {
            std::array<T, BlockSize> newBlock;
            addBlockAtFront();
            std::copy_backward(blocks[0].begin(), blocks[0].end() - 1, newBlock.end());
            newBlock[0] = val;
            blocks[0] = newBlock;
            size1 = 1;
            size2 = BlockSize;
        }
    }

    void push_back(const T& val)
    {
        if (size2 < BlockSize) 
        {
            blocks[1][size2++] = val;
        }
        else 
        {
            std::array<T, BlockSize> newBlock;
            std::copy(blocks[1].begin(), blocks[1].end(), newBlock.begin());
            newBlock[size2++] = val;
            blocks[1] = newBlock;
            size1 = 0;
            size2 = BlockSize;
        }
    }
    void pop_front() 
    {
        if (size1 > 0) 
        {
            for (size_t i = 0; i < size1 - 1; ++i)
                blocks[0][i] = blocks[0][i + 1];
            --size1;
        }
        else if (size2 > 0) 
        {
            std::copy(blocks[1].begin() + 1, blocks[1].end(), blocks[0].begin());
            --size2;
        }
    }
    void pop_back() 
    {
        if (size2 > 0)
            --size2;
        else if (size1 > 0) 
            --size1;
    }

    size_t size() const
    {
        return size1 + size2;
    }

    bool empty() const 
    {
        return size1 == 0 && size2 == 0;
    }

    const T& front() const 
    {
        if (size1 > 0) {
            return blocks[0][0];
        }
        else {
            return blocks[1][size2 - 1];
        }
    }

    const T& back() const 
    {
        if (size2 > 0) {
            return blocks[1][size2 - 1];
        }
        else {
            return blocks[0][size1 - 1];
        }
    }

    T& operator[](size_t i)
    {
        if (i < size1)
            return blocks[0][i];
        else
            return blocks[1][i - size1];
    }

    const T& operator[](size_t i) const
    {
        if (i < size1)
            return blocks[0][i];
        else
            return blocks[1][i - size1];
    }

    void insert(const T& val, size_t pos) {
        if (pos >= size1 + size2) {
            std::cerr << "Index out of range\n";
            return;
        }

        if (pos < size1) { 
            if (size1 < BlockSize) {
                for (size_t i = size1; i > pos; --i)
                    blocks[0][i] = blocks[0][i - 1];
                blocks[0][pos] = val;
                ++size1;
            }
            else {
                std::array<T, BlockSize> newBlock;
                addBlockAtFront();
                std::copy_backward(blocks[0].begin(), blocks[0].begin() + pos, newBlock.end());
                newBlock[pos] = val;
                std::copy(blocks[0].begin() + pos, blocks[0].end(), newBlock.begin() + pos + 1);
                blocks[0] = newBlock;
                size1 = 1;
                size2 = BlockSize;
            }
        }
        else { 
            pos -= size1;
            if (size2 < BlockSize) {
                for (size_t i = size2; i > pos; --i)
                    blocks[1][i] = blocks[1][i - 1];
                blocks[1][pos] = val;
                ++size2;
            }
            else {
                std::array<T, BlockSize> newBlock;
                std::copy(blocks[1].begin(), blocks[1].begin() + pos, newBlock.begin());
                newBlock[pos] = val;
                std::copy(blocks[1].begin() + pos, blocks[1].end(), newBlock.begin() + pos + 1);
                blocks[1] = newBlock;
                size1 = 0;
                size2 = BlockSize;
            }
        }
    }


    void clear()
    {
        size1 = 0;
        size2 = 0;
        for (auto& block : blocks) 
            block.fill(T{}); 

        memoryBlock.addresses.fill(nullptr);
        memoryBlock.blockCount = 0;
    }

    void print() const
    {
        for (size_t i = 0; i < size1; i++)
            std::cout << blocks[0][i]<<" ";
        for (size_t i = 0; i < size2; i++)
            std::cout << blocks[1][i] << " ";
        std::cout << '\n';
    }

    void deletePosition(size_t poz)
    {
        if (poz < size1)
        {
            for (size_t i = poz; i < size1 - 1; i++)
                blocks[0][i] = blocks[0][i + 1];
            --size1;
        }
        else
        {
            poz -= size1;
            for (size_t i = poz; i < size2 - 1; i++)
                blocks[1][i] = blocks[1][i + 1];
            --size2;
        }
    }
};

int main() {
    Deque<int, 8> deque;
    deque.push_back(1);
    deque.push_front(2);
    deque.push_back(3);
    deque.push_front(4);
    std::cout << "Deque initially: ";
    deque.print();
    int c=-1;
    while(c!=0)
    {
        std::cout << "Introduce an option: ";
        std::cin >> c;
        switch (c)
        {
        case 1:
        {
            std::cout << "Deque initially: ";
            deque.print();
            deque.push_front(10);
            std::cout << "Deque after push_front: ";
            deque.print();
            deque.push_back(20);
            std::cout << "Deque after push_back: ";
            deque.print();
            break;
        }
        case 2:
        {
            deque.pop_front();
            std::cout << "Deque after pop_front: ";
            deque.print();
            deque.pop_back();
            std::cout << "Deque after pop_back: ";
            deque.print();
            break;
        }
        case 3:
        {
            std::cout << "Front element: " << deque.front() << '\n';
            break;
        }
        case 4:
        {
            std::cout << "Back element: " << deque.back() << '\n';
            break;
        }
        case 5:
        {
            if (deque.empty())
                std::cout << "Deque is empty\n";
            else
                std::cout << "Deque is not empty\n";
            break;
        }
        case 6:
        {
            deque.clear();
            if (deque.empty())
                std::cout << "Deque is empty\n";
            else
                std::cout << "Deque is not empty\n";
            break;
        }
        case 7:
        {
            std::cout << "Deque size: " << deque.size() << '\n';
        }
        case 8:
        {
            std::cout << "Introduce a postion index: ";
            size_t i;
            std::cin >> i;
            std::cout << "The value situated at position " << i << " is: " << deque[i] << '\n';
            break;
        }
        case 9:
        {
            std::cout << "Introduce a value you want to insert: ";
            int val;
            std::cin >> val;
            std::cout << "Introduce a position: ";
            size_t poz;
            std::cin >> poz;
            deque.insert(val, poz);
            deque.print();
            break;
        }
        case 10:
        {
            std::cout << "Introduce a position you want to delete: ";
            size_t poz;
            std::cin >> poz;
            deque.deletePosition(poz);
            deque.print();
            break;
        }
        case 0:
        {
            std::cout << "Exiting program\n";
        }
        }
    }

    return 0;
}
