        #include <cmrc/cmrc.hpp>
#include <map>
#include <utility>

namespace cmrc {
namespace engine_resources {

namespace res_chars {
// These are the files which are available in this resource library
// Pointers to /Users/antoinebastide/Documents/GitHub/Perso/TestGames/Test/Engine/Shaders/particle.frag
extern const char* const f_3f7f_Engine_Shaders_particle_frag_begin;
extern const char* const f_3f7f_Engine_Shaders_particle_frag_end;
// Pointers to /Users/antoinebastide/Documents/GitHub/Perso/TestGames/Test/Engine/Shaders/particle.vert
extern const char* const f_746e_Engine_Shaders_particle_vert_begin;
extern const char* const f_746e_Engine_Shaders_particle_vert_end;
// Pointers to /Users/antoinebastide/Documents/GitHub/Perso/TestGames/Test/Engine/Shaders/shape.frag
extern const char* const f_1abe_Engine_Shaders_shape_frag_begin;
extern const char* const f_1abe_Engine_Shaders_shape_frag_end;
// Pointers to /Users/antoinebastide/Documents/GitHub/Perso/TestGames/Test/Engine/Shaders/shape.vert
extern const char* const f_ef5f_Engine_Shaders_shape_vert_begin;
extern const char* const f_ef5f_Engine_Shaders_shape_vert_end;
// Pointers to /Users/antoinebastide/Documents/GitHub/Perso/TestGames/Test/Engine/Shaders/sprite.frag
extern const char* const f_23ed_Engine_Shaders_sprite_frag_begin;
extern const char* const f_23ed_Engine_Shaders_sprite_frag_end;
// Pointers to /Users/antoinebastide/Documents/GitHub/Perso/TestGames/Test/Engine/Shaders/sprite.vert
extern const char* const f_e189_Engine_Shaders_sprite_vert_begin;
extern const char* const f_e189_Engine_Shaders_sprite_vert_end;
}

namespace {

const cmrc::detail::index_type&
get_root_index() {
    static cmrc::detail::directory root_directory_;
    static cmrc::detail::file_or_directory root_directory_fod{root_directory_};
    static cmrc::detail::index_type root_index;
    root_index.emplace("", &root_directory_fod);
    struct dir_inl {
        class cmrc::detail::directory& directory;
    };
    dir_inl root_directory_dir{root_directory_};
    (void)root_directory_dir;
    static auto f_7bfa_Engine_dir = root_directory_dir.directory.add_subdir("Engine");
    root_index.emplace("Engine", &f_7bfa_Engine_dir.index_entry);
    static auto f_aa09_Engine_Shaders_dir = f_7bfa_Engine_dir.directory.add_subdir("Shaders");
    root_index.emplace("Engine/Shaders", &f_aa09_Engine_Shaders_dir.index_entry);
    root_index.emplace(
        "Engine/Shaders/particle.frag",
        f_aa09_Engine_Shaders_dir.directory.add_file(
            "particle.frag",
            res_chars::f_3f7f_Engine_Shaders_particle_frag_begin,
            res_chars::f_3f7f_Engine_Shaders_particle_frag_end
        )
    );
    root_index.emplace(
        "Engine/Shaders/particle.vert",
        f_aa09_Engine_Shaders_dir.directory.add_file(
            "particle.vert",
            res_chars::f_746e_Engine_Shaders_particle_vert_begin,
            res_chars::f_746e_Engine_Shaders_particle_vert_end
        )
    );
    root_index.emplace(
        "Engine/Shaders/shape.frag",
        f_aa09_Engine_Shaders_dir.directory.add_file(
            "shape.frag",
            res_chars::f_1abe_Engine_Shaders_shape_frag_begin,
            res_chars::f_1abe_Engine_Shaders_shape_frag_end
        )
    );
    root_index.emplace(
        "Engine/Shaders/shape.vert",
        f_aa09_Engine_Shaders_dir.directory.add_file(
            "shape.vert",
            res_chars::f_ef5f_Engine_Shaders_shape_vert_begin,
            res_chars::f_ef5f_Engine_Shaders_shape_vert_end
        )
    );
    root_index.emplace(
        "Engine/Shaders/sprite.frag",
        f_aa09_Engine_Shaders_dir.directory.add_file(
            "sprite.frag",
            res_chars::f_23ed_Engine_Shaders_sprite_frag_begin,
            res_chars::f_23ed_Engine_Shaders_sprite_frag_end
        )
    );
    root_index.emplace(
        "Engine/Shaders/sprite.vert",
        f_aa09_Engine_Shaders_dir.directory.add_file(
            "sprite.vert",
            res_chars::f_e189_Engine_Shaders_sprite_vert_begin,
            res_chars::f_e189_Engine_Shaders_sprite_vert_end
        )
    );
    return root_index;
}

}

cmrc::embedded_filesystem get_filesystem() {
    static auto& index = get_root_index();
    return cmrc::embedded_filesystem{index};
}

} // engine_resources
} // cmrc
    