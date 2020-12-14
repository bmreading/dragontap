sources = [
    'wt-application.c',
    'wt-window.c',
    'wt-network-manager.c',
    'main.c'
]

dependencies = [
    gtk_dep,
    nm_dep
]

executable(
    meson.project_name(),
    wt_resources,
    sources: sources,
    dependencies: dependencies
)