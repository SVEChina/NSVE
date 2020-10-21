{
    "vdsp" : ["E_V2","E_T0"],
    "pass" : "direct",
    "vs" : "shader/code/screen.vs",
    "fs" : "shader/code/filter/filterColorBalance.fs",
    "sampler": [ { "name" : "aTexture0", "stage" : 1 , "chn" : 0 } ],
    "uniform": [
        {
            "stage" : 1,
            "bufID" : 1,
            "tbl" :[
                { "name" : "redShift", "type" : "f32", "value" : "1.0" },
                { "name" : "greenShift", "type" : "f32", "value" : "1.0" },
                { "name" : "blueShift", "type" : "f32", "value" : "1.0" }
            ]
        }
    ]
}
