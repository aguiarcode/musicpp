target("musicpp")
    set_kind("binary")
    set_languages("cxx17")
    add_files("src/**.cpp")
    add_includedirs("src", "include", "third_party")

    if is_os("windows") then
        add_syslinks("ole32", "user32")
    end
