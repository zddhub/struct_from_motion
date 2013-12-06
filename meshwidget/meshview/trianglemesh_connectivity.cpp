//�����������ͨ��


#include "trianglemesh.h"

#include <algorithm>
using namespace std;


//����ÿ�������ֱ���ھӶ���
void TriangleMesh::need_neighbors()
{
    if(!neighbors.empty())
        return;

    need_faces();
    if(faces.empty())
        return;

    dprintf("Find vertex neighbors...");
    int nv = vertices.size(), nf = faces.size();

    vector<int> numneighbors(nv);
    for(int i = 0; i < nf; i++)
    {
        numneighbors[faces[i][0]]++;
        numneighbors[faces[i][1]]++;
        numneighbors[faces[i][2]]++;
    }

    //vector ��reserve������vector��capacity����������sizeû�иı䣡��resize�ı���vector��capacityͬʱҲ����������size��

    neighbors.resize(nv);
    for(int i = 0; i < nv; i++)
    {
        neighbors[i].reserve(numneighbors[i] + 2);//��ֹ�߽����
    }

    for(int i = 0; i < nf; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            vector<int> &me = neighbors[faces[i][j]];
            int n1 = faces[i][(j+1)%3]; //������������
            int n2 = faces[i][(j+2)%3];
            if(find(me.begin(), me.end(), n1) == me.end())
                me.push_back(n1);
            if(find(me.begin(), me.end(), n2) == me.end())
                me.push_back(n2);
        }
    }

    dprintf("Done.\n");
}

//ÿ�������ڽӵ���Ƭ
void TriangleMesh::need_adjacentfaces()
{
    if(!adjacentfaces.empty())
        return;

    need_faces();
    if(faces.empty())
        return;

    dprintf("Find adjacent faces...");

    int nv = vertices.size(), nf = faces.size();

    vector<int> numadjacentfaces(nv);
    for(int i = 0; i < nf; i++)
    {
        numadjacentfaces[faces[i][0]]++;
        numadjacentfaces[faces[i][1]]++;
        numadjacentfaces[faces[i][2]]++;
    }

    adjacentfaces.resize(nv);
    for(int i = 0; i < nv; i++)
    {
        adjacentfaces[i].reserve(numadjacentfaces[i]);
    }

    for(int i = 0; i < nf; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            adjacentfaces[faces[i][j]].push_back(i);
        }
    }

    dprintf("Done.\n");
}

// Find the face across each edge from each other face (-1 on boundary)
// If topology is bad, not necessarily what one would expect...//������ :)
//  ���磺across_edge[3][2]��ʾ��������Ƭ���(faces[across_edge[3][2]]Ϊ����������Ƭ)
//  �����������4(�±�Ϊ3)��������(faces[3])�й����ߣ�������Ϊfaces[3]���±�Ϊ[2]�Ķ������Եı�
void TriangleMesh::need_across_edge()
{
    if(!across_edge.empty())
        return;

    need_adjacentfaces();
    if(adjacentfaces.empty())
        return;

    dprintf("Finding across-edge maps... ");

    int nf = faces.size();
    across_edge.resize(nf, Face(-1, -1, -1));

#pragma omp parallel for
    for(int i = 0; i < nf; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(across_edge[i][j] != -1)
                continue;
            int v1 = faces[i][(j+1) % 3];
            int v2 = faces[i][(j+2) % 3];
            const vector<int>& a1 = adjacentfaces[v1];
            const vector<int>& a2 = adjacentfaces[v2];
            for(int k1 = 0; k1 < a1.size(); k1++)
            {
                int other = a1[k1];
                if(other == i)
                    continue;
                vector<int>::const_iterator it = find(a2.begin(), a2.end(), other);
                if(it == a2.end())
                    continue;
                int ind = (faces[other].indexof(v1)+1)%3;
                if(faces[other][(ind+1)%3] != v2)
                    continue;
                across_edge[i][j] = other;
                across_edge[other][ind] = i;
                break;
            }
        }
    }

    dprintf("Done.\n");
}
