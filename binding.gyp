{
  "targets": [{
      "target_name": "pifacedigital",
      "include_dirs": [ 
          '/usr/local/include', 
          "<!(node -e \"require('nan')\")",
          "<!@(node -p \"require('node-addon-api').include\")"
      ],
     'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],      
      "sources": [
        "src/cpp/init.cpp",
        "src/cpp/pfdig.cpp"
      ],
      "link_settings":{
        "libraries": [
            "-lpifacedigital",
            "-lmcp23s17"
        ]
      }
 }]
}
