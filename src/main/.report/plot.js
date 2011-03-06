function plot( results ) {

    console.log('results: ' + JSON.stringify(results));

    var lines = [];
    var series = [];
    var ticks = [];
    for (var index in results ) {	
	var result = results[index];

	var line = [ result['avg'] ];
	lines.push(line);

	var label = { renderer:$.jqplot.BarRenderer, label : result['lang_rt'] } ;
	series.push(label);

    }

    line1 = [1,4,9, 16];
    line2 = [25, 12.5, 6.25, 3.125];
    plot1 = $.jqplot('chart1', lines, {
	    'legend':{ 'show':true, 'location':'nw'},title:'Performance Comparion - 15-Hole Peg Solitaire - Using Object Oriented Style',
	    'series': series,
	    'axes':{
		xaxis:{
		    renderer:$.jqplot.CategoryAxisRenderer

		},
		yaxis:{
		    label:'Time (ms)',
		    min: 0
		}
	    }
	});
    
}
