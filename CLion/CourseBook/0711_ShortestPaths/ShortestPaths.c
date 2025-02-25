/*====================
 * 最短路径算法
 *
 * 包含算法: 7.15、7.16
 =====================*/

#include "ShortestPaths.h"

/*
 * ████████ 算法7.15 ████████
 *
 * 迪杰斯特拉(Dijkstra)算法求单源最短路径
 *
 * @param G  待遍历的图。
 * @param v0 单源最短路径的起点。
 * @param P  存储从v0到其余各顶点的最短路径信息。
 *           P[j][k]==TRUE代表从v0->j的最短路径会经过顶点k；否则，代表不经过。
 *           注：
 *           1.该数组只反映了顶点的存在性，而未反映顶点在路径上的次序。
 *           2.如果两顶点之间有多条最短路径，只会选取一条
 * @param D  存储从v0到其余各顶点的最短路径代价，在图中，该代价是步长和，在网中，该代价是权值和。
 */
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix_DIJ P, ShortPathTable_DIJ D) {
    int v, w, i, j, min;
    Status final[MAX_VERTEX_NUM];   // 用来标记当前结点是否已经访问过，即是否已加入最短路径
    
    /*
     * 预设已访问过的顶点集为S，未访问过的顶点集为V-S
     * 初始时，顶点集S为空，而顶点集V-S为所有顶点的集合V
     */
    for(v = 0; v < G.vexnum; v++) {
        // 初始时，所有顶点均未访问过
        final[v] = FALSE;
        
        // 初始化v0->v的路径代价
        D[v] = G.arcs[v0][v].adj;
        
        // 预设从v0->v不需要经过顶点w，即设空路径
        for(w = 0; w < G.vexnum; w++) {
            P[v][w] = FALSE;
        }
        
        // 如果是网，只走此分支(教材只处理了此种情形)
        if(G.kind == DN || G.kind == UDN) {
            // 如果v0->v直接连通
            if(D[v] < INFINITE) {
                P[v][v0] = TRUE;    // 指示v0->v必将经过顶点v0(端点一)
                P[v][v] = TRUE;     // 指示v0->v必将经过顶点v(端点二)
            }
        }
        
        // 如果是图，只走此分支
        if(G.kind == DG || G.kind == UDG) {
            // 如果v0到v直接连通
            if(D[v] != 0) {
                P[v][v0] = TRUE;    // 指示v0->v必将经过顶点v0(端点一)
                P[v][v] = TRUE;     // 指示v0->v必将经过顶点v(端点二)
            }
        }
    }
    
    // 初始化，v0进入顶点集S
    D[v0] = 0;
    final[v0] = TRUE;
    
    /*
     * 开始主循环，遍历其余G1.vexnum-1个顶点。
     * 每次求得v0到某个顶点的最短路径，则将该顶点从顶点集V-S中挪到顶点集S中
     */
    for(i = 1; i < G.vexnum; i++) {
        /*
         * 每次进入选取最近顶点之前，都应当将v重置为一个正常顶点序号之外的值
         * (教材中无此步骤，需要补上，否则会进行很多次无效的循环)
         */
        v = -1;
        
        // 记录各顶点与顶点v0的最短距离
        min = INFINITE;
        
        // 遍历顶点集V-S(所有未加入路径的顶点)，从中选出距离v0更近的顶点
        for(w = 0; w < G.vexnum; w++) {
            // 如果w顶点在V-S中(未加入最短路径)
            if(!final[w]) {
                // 对于图来说，距离为0意味着两顶点不连通
                if((G.kind == DG || G.kind == UDG) && D[w] == 0) {
                    continue;
                }
                
                // 如果v0到w的距离D[w]小于当前预设的最小距离，则需要更新顶点和距离信息
                if(D[w] < min) {
                    v = w;      // 记下未访问的顶点中距离v0更近的顶点，或者可以理解为记下顶点集V-S中距离顶点集S更近的顶点
                    min = D[w]; // 记下更近的距离
                }
            }
        }
        
        // 找到了更近的顶点
        if(v != -1) {
            // 将顶点集V-S中当前距离v0顶点最近的v加入S集
            final[v] = TRUE;
        } else {
            // 如果没找到更近的顶点，说明顶点v0与V-S中的剩余顶点没有连接，此时可以直接结束程序了
            return;
        }
        
        // 以上述的顶点v做跳板，更新顶点v0到V-S集中其余点顶点的最短路径
        for(w = 0; w < G.vexnum; w++) {
            // 如果是网，只走此分支(教材只处理了此种情形)
            if(G.kind == DN || G.kind == UDN) {
                /*
                 * 为了避免溢出，需要确保G.arcs[v][w].adj不为INFINITE。
                 * 此处其实没必要判断min!=INFINITE，因为如果没找到更近的顶点时，上面就提前返回了。
                 * (教材的伪码中未处理溢出，故需要自行添加)
                 */
                if(min != INFINITE && G.arcs[v][w].adj != INFINITE) {
                    // 更新顶点集S到顶点集V-S的最近距离
                    if(!final[w] && (min + G.arcs[v][w].adj < D[w])) {
                        // 更新距离：由于顶点v0->w经由v后会获得更短的距离，故此处需要记下该距离
                        D[w] = min + G.arcs[v][w].adj;
                        
                        /* 更新路径：P[w] = P[v] + [w] */
                        
                        // 先将v0->w的路径更新为v0->j的路径
                        for(j = 0; j < G.vexnum; j++) {
                            P[w][j] = P[v][j];
                        }
                        
                        // 再将w添加到v0->w的路径中
                        P[w][w] = TRUE;
                    }
                }
            }
            
            // 如果是图，只走此分支
            if(G.kind == DG || G.kind == UDG) {
                // 更新顶点集S到顶点集V-S的最近距离
                if(!final[w] && G.arcs[v][w].adj != 0 ) {//&& D[w] == 0
                    if (D[w] == 0 || ((D[v] + 1)<D[w]))//之前没有路，或者经过v的路更短，则经过V
                    {
                        // 更新距离：由于顶点v0->w经由v后会获得更短的距离，故此处需要记下该距离
                        D[w] = D[v] + 1;    // 图中相邻顶点步长为1

                        /* 更新路径：P[w] = P[v] + [w] */

                        // 先将v0->w的路径更新为v0->j的路径
                        for(j = 0; j < G.vexnum; j++) {
                            P[w][j] = P[v][j];
                        }

                        // 再将w添加到v0->w的路径中
                        P[w][w] = TRUE;
                    }

                }
            }
        }
    }
}

/*
 * 打印使用迪杰斯特拉(Dijkstra)算法求取的单源最短路径
 */
void PrintPath_DIJ(MGraph G, int v0, PathMatrix_DIJ P, ShortPathTable_DIJ D) {
    int j;
    
    // 遍历所有路径
    for(j = 0; j < G.vexnum; j++) {
        if(P[j][v0] == FALSE) {
            printf("%c 到 %c 之间没有通路\n", GetVex(G, v0), GetVex(G, j));
            continue;
        }
        
        printf("%c 到 %c 之间的最短距离为%2d，其最短路径为：", GetVex(G, v0), GetVex(G, j), D[j]);
        
        /*
         * 将v0->j之间的无序顶点排列成一条有序路径后打印
         * P[i]指示v0->j这条路径上经过的顶点
         */
        PrintPath(G, v0, j, P[j]);
    }
}

/*
 * ████████ 算法7.16 ████████
 *
 * 弗洛伊德(Floyd)算法求多源最短路径
 *
 * @param G  待遍历的图。
 * @param P  存储各对顶点之间的最短路径信息。
 *           P[i][j][k]==TRUE代表从i->j的最短路径会经过顶点k；否则，代表不经过。
 *           注：该数组只反映了顶点的存在性，而未反映顶点在路径上的次序。
 * @param D  存储各对顶点之间的最短路径代价，在图中，该代价是步长和，在网中，该代价是权值和。
 */
void ShortestPath_FLOYD(MGraph G, PathMatrix_FLOYD P, ShortPathTable_FLOYD D) {
    int i, v, w, u;
    
    // 对各顶点之间初始已知路径及距离
    for(v = 0; v < G.vexnum; v++) {
        for(w = 0; w < G.vexnum; w++) {
            // 获取<v,w>的边/弧信息
            D[v][w] = G.arcs[v][w].adj;
            
            // 初始化路径v->w为空路径
            for(u = 0; u < G.vexnum; u++) {
                P[v][w][u] = FALSE;
            }
            
            // 如果是网，只走此分支(教材只处理了此种情形)
            if(G.kind == DN || G.kind == UDN) {
                // 如果v0->v直接连通
                if(D[v][w] < INFINITE) {
                    P[v][w][v] = TRUE;  // 指示v->w必将经过顶点v(端点一)
                    P[v][w][w] = TRUE;  // 指示v->w必将经过顶点w(端点二)
                }
            }
            
            // 如果是图，只走此分支
            if(G.kind == DG || G.kind == UDG) {
                // 如果v0->v直接连通
                if(D[v][w] != 0) {
                    P[v][w][v] = TRUE;  // 指示v->w必将经过顶点v(端点一)
                    P[v][w][w] = TRUE;  // 指示v->w必将经过顶点w(端点二)
                }
            }
        }
    }
    
    for(u = 0; u < G.vexnum; u++) {
        for(v = 0; v < G.vexnum; v++) {
            for(w = 0; w < G.vexnum; w++) {
                // 对于同一顶点，将其视为不连通
                if(v == w) {
                    continue;
                }
                
                // 如果是网，只走此分支(教材只处理了此种情形)
                if(G.kind == DN || G.kind == UDN) {
                    // 需要先判断权值信息，防止溢出
                    if(D[v][u] != INFINITE && D[u][w] != INFINITE) {
                        // 从v经u到w(v->u->w)的一条路径更短
                        if(D[v][u] + D[u][w] < D[v][w]) {
                            // 更新权值
                            D[v][w] = D[v][u] + D[u][w];
                            
                            // 更新路径
                            for(i = 0; i < G.vexnum; i++) {
                                P[v][w][i] = P[v][u][i] || P[u][w][i];
                            }
                        }
                    }
                }
                
                // 如果是图，只走此分支
                if(G.kind == DG || G.kind == UDG) {
                    // 需要先判断连接信息
                    if(D[v][u] != 0 && D[u][w] != 0) {
                        // 从v经u到w(v->u->w)的一条路径更短
                        if(D[v][w] == 0 || D[v][u] + D[u][w] < D[v][w]) {
                            // 更新权值
                            D[v][w] = D[v][u] + D[u][w];
                            
                            // 更新路径
                            for(i = 0; i < G.vexnum; i++) {
                                P[v][w][i] = P[v][u][i] || P[u][w][i];
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
 * 打印使用弗洛伊德(Floyd)算法求取的单源最短路径
 */
void PrintPath_FLOYD(MGraph G, PathMatrix_FLOYD P, ShortPathTable_FLOYD D) {
    int i, j;
    
    // 遍历所有路径
    for(i = 0; i < G.vexnum; i++) {
        for(j = 0; j < G.vexnum; j++) {
            if(P[i][j][i] == FALSE) {
                printf("%c 到 %c 之间没有通路\n", GetVex(G, i), GetVex(G, j));
                continue;
            }
            
            printf("%c 到 %c 之间的最短距离为%2d，其最短路径为：", GetVex(G, i), GetVex(G, j), D[i][j]);
            
            /*
             * 将i->j之间的无序顶点排列成一条有序路径后打印
             * P[i][j]指示i->j这条路径上经过的顶点
             */
            PrintPath(G, i, j, P[i][j]);
        }
    }
}

/*
 * 打印从a到b的路径，该路径的顶点信息位于P中
 */
static void PrintPath(MGraph G, int a, int b, Boolean P[MAX_VERTEX_NUM]) {
    int i;
    int vexs[MAX_VERTEX_NUM + 1];
    int path[MAX_VERTEX_NUM + 1];
    
    vexs[0] = 0;
    
    // 获取v0->i这条途径上的所有顶点，可能是无序的
    for(i = 0; i < G.vexnum; i++) {
        if(P[i] == TRUE) {
            vexs[0]++;
            vexs[vexs[0]] = i;
        }
    }
    
    // 只有两个顶点的情形下快速处理
    if(vexs[0] == 2) {
        path[0] = 2;
        path[1] = a;
        path[2] = b;
        goto print;
    }
    
    // 只有三个顶点的情形下快速处理
    if(vexs[0] == 3) {
        path[0] = 3;
        path[1] = a;
        for(i = 1; i <= vexs[0]; i++) {
            if(vexs[i] != a && vexs[i] != b) {
                path[2] = vexs[i];
                break;
            }
        }
        path[3] = b;
        goto print;
    }
    
    path[0] = 1;
    path[1] = a;
    
    for(i = 1; i <= vexs[0]; i++) {
        if(vexs[i] == a) {
            vexs[i] = -1;
            break;
        }
    }
    
    Find(G, a, b, vexs, path);

print:
    // 打印排列好的路径
    for(i = 1; i <= path[0]; i++) {
        printf("%c ", GetVex(G, path[i]));
    }
    
    printf("\n");
}

/*
 * 利用广度预先搜索找到一条从pre到b的路径，该路径上路过的所有顶点位于vexs中，找出的路径存储到path中
 */
static Status Find(MGraph G, int pre, int b, int vexs[MAX_VERTEX_NUM + 1], int path[MAX_VERTEX_NUM + 1]) {
    int i;
    int tmp;
    Status s;
    
    for(i = 1; i <= vexs[0]; i++) {
        // 已加入到路径
        if(vexs[i] == -1) {
            continue;
        }
        
        // 不连通
        if(((G.kind == DN || G.kind == UDN) && G.arcs[pre][vexs[i]].adj == INFINITE)
        || ((G.kind == DG || G.kind == UDG) && G.arcs[pre][vexs[i]].adj == 0)) {
            continue;
        }
        
        path[0]++;
        path[path[0]] = vexs[i];
        
        // 遇到终点
        if(vexs[i] == b) {
            // 找到了最短路径
            if(path[0] == vexs[0]) {
                return OK;
            } else {
                path[0]--;
                continue;
            }
        }
        
        tmp = vexs[i];
        vexs[i] = -1;
        
        s = Find(G, tmp, b, vexs, path);
        
        if(s == OK) {
            return OK;
        } else {
            // 恢复该顶点，以便后续重新搜索
            vexs[i] = tmp;
            path[0]--;
        }
    }
    
    return ERROR;
}
