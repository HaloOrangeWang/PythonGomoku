#include <stdio.h>
#include <stdlib.h>
#include <Python.h>
#include "ai.h"

Point ai_1step(int p_init_map[225], int init_depth, bool player_first, uint64_t max_depth, int& tree_size)
{
    // 1 转换参数
    int init_map[15][15];
    for (int t = 0; t <= 224; t++){
        init_map[t / 15][t % 15] = p_init_map[t];
    }
    //max_depth = static_cast<uint64_t>(atoi(p_max_depth));

    char g[550];
    sprintf(g, "%d %d %d.\n", init_depth, player_first, max_depth);

    // 2 进行运算
    AI1Step* pai = new AI1Step(init_map, init_depth, player_first);
    pai->Search(0, max_depth);

    // 3 输出游戏结果
    Point FinalRes = pai->GetFinalRes();
    tree_size = pai->MethodTree.size();
    return FinalRes;
    //printf("%d\n%d\n%d\n", pai->MethodTree.size(), FinalRes.X, FinalRes.Y);
}

PyObject* wrap_ai_1step(PyObject* self, PyObject* args)
{
    PyObject* init_map_origin;
    int init_depth_origin;
    int player_first_origin;
    int max_depth_origin;

    int init_map[225];
    int init_depth;
    bool player_first;
    uint64_t max_depth;

    if (!PyArg_ParseTuple(args, "iiiO", &init_depth_origin, &player_first_origin, &max_depth_origin, &init_map_origin))
    {
        printf("Parse Tuple失败\n");
        return NULL;
    }

    for (int t = 0; t <= 224; t++){
        PyObject *item = PyList_GetItem(init_map_origin, t);
        if (!PyLong_Check(item))
        {
            printf("Index %d 不能转化成整数.\n", t);
            return NULL;
        }else
            init_map[t] = PyLong_AsLong(item);
    }
    init_depth = init_depth_origin;
    player_first = static_cast<bool>(player_first_origin);
    max_depth = static_cast<uint64_t>(max_depth_origin);
    int tree_size;
    Point res = ai_1step(init_map, init_depth, player_first, max_depth, tree_size);
    return Py_BuildValue("iii", tree_size, res.X, res.Y);
}

static PyMethodDef exampleMethods[] =
{
    {"ai_1step", wrap_ai_1step, METH_VARARGS, "f(a, b) = a + b - 1"},
    {NULL, NULL, 0, NULL}
};

// void initexample()
// {
//     PyObject* m;
//     m = Py_InitModule("example", exampleMethods);
// }

static struct PyModuleDef example =
{
    PyModuleDef_HEAD_INIT,
    "example", /* name of module */
    "No documentation", /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    exampleMethods
};

PyMODINIT_FUNC PyInit_example(void)
{
    return PyModule_Create(&example);
}
