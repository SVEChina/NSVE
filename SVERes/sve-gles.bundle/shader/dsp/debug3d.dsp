{
    "vdsp" : ["E_V2","E_T0"],
    "pass" : "direct",
    "vs" : "shader/code/debug/debug3d.vs",
    "fs" : "shader/code/debug/debug.fs",
    "uniform": [
        {
            "stage" : 0,
            "bufID" : 1,
            "tbl" : [ { "name" : "matw", "type" : "fmat4", "value" : "null" },
                      { "name" : "matvp", "type" : "fmat4", "value" : "null" },
                      { "name" : "u_color", "type" : "fvec3", "value" : "0.0,1.0,0.0" } ]
        }
    ]
}
