sources = [
    'dt-application.c',
    'dt-window.c',
    'dt-network-manager.c',
    'dt-row.c',
    'main.c'
]

dependencies = [
    gtk_dep,
    nm_dep
]

executable(
    meson.project_name(),
    dt_resources,
    sources: sources,
    dependencies: dependencies
)