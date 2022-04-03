// #include <bits/stdc++.h>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Bucket
{
public:
    int localDepth;
    set<int> s;
    Bucket(int depth)
    {
        localDepth = depth;
    };
};

class Directory
{
public:
    Directory(int depth, int bSize)
    {
        globalDepth = depth;
        bucketSize = bSize;
        bucketDir.resize(1 << depth);
        for (int i = 0; i < (1 << depth); i++)
        {
            bucketDir[i] = new Bucket(depth);
            index.push_back(i);
        }
    };

private:
    int globalDepth;
    int bucketSize;
    vector<Bucket *> bucketDir;
    vector<int> index;

public:
    void insertKey(int key)
    {
        int mod;
        mod = key % (1 << globalDepth);
        if (bucketDir[mod]->s.size() == bucketSize)
        {
            if (bucketDir[mod]->localDepth == globalDepth)
            {
                if (globalDepth == 20)
                {
                    cout << "global depth cannot go above 20" << endl;
                    return;
                }
                
                for (int i = 0; i < (1 << globalDepth); i++)
                {
                    bucketDir.push_back(bucketDir[i]);
                }
                globalDepth++;
                insertKey(key);
            }
            else
            {
                Bucket *old = bucketDir[mod];
                int temp = old->localDepth;
                int smallestBucket = (mod % (1 << temp));
                bucketDir[smallestBucket] = new Bucket(temp + 1);
                bucketDir[smallestBucket + (1 << (temp))] = new Bucket(temp + 1);
                index.push_back(smallestBucket + (1 << (temp)));

                int bucketAssign = smallestBucket;

                for (int i = 0; i < 1 << (globalDepth - temp - 1); i++)
                {
                    bucketDir[bucketAssign] = bucketDir[smallestBucket];
                    bucketDir[bucketAssign + (1 << (temp))] = bucketDir[smallestBucket + (1 << (temp))];
                    bucketAssign += 2 * (1 << temp);
                }

                for (auto x : (old->s))
                {
                    insertKey(x);
                }
                delete (old);
                insertKey(key);
            }
        }
        else
        {
            bucketDir[mod]->s.insert(key);
        }
    }
    bool search(int key)
    {
        int mod;
        mod = key % (1 << globalDepth);
        bool ans;
        if (bucketDir[mod]->s.find(key) == bucketDir[mod]->s.end())
        {
            ans = false;
        }
        else
        {
            ans = true;
        }
        return ans;
    };
    void del(int key)
    {
        int mod;
        mod = key % (1 << globalDepth);
        if (search(key))
        {
            bucketDir[mod]->s.erase(bucketDir[mod]->s.find(key));
        }
    };
    void display()
    {
        cout << globalDepth << endl;
        cout << index.size() << endl;

        for (int i = 0; i < index.size(); i++)
        {
            cout << bucketDir[index[i]]->s.size() << " " << bucketDir[index[i]]->localDepth;
            if (i != index.size() - 1)
            {
                cout << endl;
            }
        }
        cout << endl;
    };
};

int main()
{
    int globalDepth, bucketSize, operation;
    cin >> globalDepth;
    cin >> bucketSize;

    Directory instance(globalDepth, bucketSize);

    while (cin >> operation)
    {
        switch (operation)
        {
            case 2:
            {
                int data;
                cin >> data;
                instance.insertKey(data);
                break;
            }

            case 3:
            {
                int data;
                cin >> data;
                instance.search(data);
                break;
            }

            case 4:
            {
                int data;
                cin >> data;
                instance.del(data);
                break;
            }

            case 5:
            {
                instance.display();
                break;
            }

            case 6:
            {
                return 0;
            }
        }
    }
    return 0;
}
