{
  "targets": [{
      "target_name": "pifacedigital",
      "include_dirs": [ '/usr/local/include', "<!(node -e \"require('nan')\")" ],
      "sources": [
        "src/cpp/init.cc",
        "src/cpp/NPIFaceDigital.cc"
      ],
      "link_settings":{
        "libraries": [
            "-lpifacedigital",
            "-lmcp23s17"
        ]
      }
 }]
}
