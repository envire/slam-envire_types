Vizkit::UiLoader.register_3d_plugin('OcTreeVisualization', 'octomap', 'OcTreeVisualization')
Vizkit::UiLoader.register_3d_plugin_for('OcTreeVisualization', "/boost/shared_ptr</octomap/AbstractOcTree>", :updateData )
Vizkit::UiLoader.register_3d_plugin_for('OcTreeVisualization', "/envire/core/SpatioTemporal</boost/shared_ptr</octomap/AbstractOcTree>>") do |plugin,sample,_|
    if plugin.getVisualizationFrames.include? sample.frame_id
        plugin.setVisualizationFrame(sample.frame_id)
    end
    plugin.updateData(sample.data)
end