{
    "vdsp" : ["E_V2","E_T0","E_T1"],
    "pass" : "direct",
    "vs" : "shader/code/debug/mask.vs",
    "fs" : "shader/code/debug/maskNormal.fs",
    "uniform": [
        {
            "stage" : 1,
            "bufID" : 1,
            "tbl" :[ { "name" : "uTex0size", "type" : "fvec2", "value" : "720.0, 1280.0" },
                     { "name" : "uTex1size", "type" : "fvec2", "value" : "720.0, 1280.0" },
                     { "name" : "uInvert0", "type" : "fvec2", "value" : "1.0,1.0" },
                        { "name" : "uInvert1", "type" : "fvec2", "value" : "1.0,1.0" }
                      ]
        }
    ]
}
