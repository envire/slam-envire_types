Vizkit::UiLoader.register_3d_plugin('OcTreeVisualization', 'octomap', 'OcTreeVisualization')
Vizkit::UiLoader.register_3d_plugin_for('OcTreeVisualization', "/octomap/AbstractOcTreePtr", :updateData )
Vizkit::UiLoader.register_3d_plugin_for('OcTreeVisualization', "/envire/core/SpatioTemporal</octomap/AbstractOcTreePtr>") do |plugin,sample,_|
    if plugin.getVisualizationFrames.include? sample.frame_id
        plugin.setVisualizationFrame(sample.frame_id)
    end
    plugin.updateData(sample.data)
end