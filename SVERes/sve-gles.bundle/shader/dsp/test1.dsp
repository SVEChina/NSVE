{
    "vdsp" : ["E_V3","E_T0"],
    "pass" : "nor",
    "vs" : "shader/code/test1.vs",
    "fs" : "shader/code/test1.fs",
    "sampler": [ { "name" : "aTexture0", "stage" : 1 , "chn" : 0 } ],
    "uniform": [
        {
            "stage" : 0,
            "bufID" : 1,
            "tbl" : [
                        { "name" : "matw", "type" : "fmat4", "value" : "null" },
                        { "name" : "matvp", "type" : "fmat4", "value" : "null" },
                        { "name" : "texcoordClip", "type" : "fvec2", "value" : "null" }
                    ]
        }
    ]
}
