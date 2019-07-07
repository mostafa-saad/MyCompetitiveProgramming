#!/usr/bin/env python3
import sys

def citations():
    n = int(sys.stdin.readline().strip())
    time = []
    children = []
    isroot = [True] * n
    for i in range(n):
        data = list(map(int, sys.stdin.readline().split()))
        time.append(data[0])
        children.append(data[2:])
        for i in range(len(children[-1])):
            child = children[-1][i] - 1
            isroot[child] = False
            children[-1][i] = child
            
    root = 0
    for i in range(n):
        if isroot[i]:
            root = i
            
    timeneeded = [-1] * n
    subtreesize = [-1] * n
    penalty = [-1] * n
    
    # Stack-based DFS
    seen = [False] * n
    depth = [-1] * n
    depth[root] = 0
    stack = [root]
    while len(stack) > 0:
        node = stack[-1]
        if not seen[node]:
            # Pre-processing step of DFS
            seen[node] = True
            for child in children[node]:
                depth[child] = depth[node] + 1
                stack.append(child)
        else:
            # Post-processing step of DFS
            node = stack.pop()
            timeneeded[node] = time[node] + 1
            subtreesize[node] = 1
            
            pen = 0
            timesofar = 1
            
            if len(children[node]) >= 1:
                children[node].sort(key=lambda x: -subtreesize[x])
                
                for child in children[node]:
                    timeneeded[node] += timeneeded[child]
                    subtreesize[node] += subtreesize[child]
                    
                    pen += penalty[child] + timesofar * subtreesize[child]
                    timesofar += timeneeded[child]
            
            penalty[node] = pen + timeneeded[node]
            
            # print("Processed", node, "children",children[node],
            #      "readtime", time[node], "timeneeded", timeneeded[node],
            #      "subtreesize", subtreesize[node], "penalty", penalty[node])
       
    
    return penalty[root]
    

print(citations())