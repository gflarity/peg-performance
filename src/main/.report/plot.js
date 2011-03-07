function plot( results ) {

    console.log('results: ' + JSON.stringify(results));

    var lines = [];
    var series = [];
    var ticks = [];
    for (var index in results ) {	
	var result = results[index];
	var label = result['lang_rt'] + ' - ' +  result['avg'] + 'ms';
	var line = [ result['avg'] ];
	lines.push(line);
	var serie = { 
	    label : label,
	    pointLabels:{
		labels:['fourteen' ]
	    }
	};
	series.push(serie);

    }

    line1 = [1,4,9, 16];
    line2 = [25, 12.5, 6.25, 3.125];

    plot1 = $.jqplot('chart1', lines, {
	    'legend':{ 
		'show':true, 
		'location':'nw'},
	    title:'Performance Comparion - 15-Hole Peg Solitaire - Using Object Oriented Style',
	    seriesDefaults: {renderer: $.jqplot.BarRenderer},
	    series: series,	    
	    axes:{
		xaxis:{
		    renderer:$.jqplot.CategoryAxisRenderer
		},
		yaxis:{
		    label:'Time (ms)',
		    min: 0
		}
	    },
	});
    
}
