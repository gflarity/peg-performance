var child_process = require('child_process');
var fs = require('fs');
var path = require('path');
var dir_contents = fs.readdirSync( './' );

sum = function( array ) {

    var sum = 0;
    for ( var index in array ) {
	sum = sum + array[index];
    }

    return sum;

};

avg = function(array) {

    return Math.ceil(sum( array ) / array.length);

};

function process_dir( dir )
{
    
    //parse the result files
    var times = [];
    var cwd = process.cwd();
    
    var result_file =  dir + '/result';

    if ( ! path.existsSync( result_file ) ) {
	return null; 
    }
	
    var results = fs.readFileSync( result_file, encoding = 'utf8'  );
    var lang_rt = results.split('\n')[0];
    var lang = lang_rt.split( ' - ' )[0];
    var regex = /\s(\d+)ms/g;

    var matches = results.match( regex );
    if ( matches ) {
	//	console.log(matches);
	for (var index in matches ) {
	    var match = matches[index];
	    match.replace( /\s+/, '' );
	    match.replace( /ms/, '' );
	    var time = parseInt(match);
	    times.push(time);
	}

    }

    //drop the highest and lowest
    times.sort();
    times = times.slice(1, -1 );
    

    return { lang_rt : lang_rt + ' - ' + avg(times), times : times, avg : avg(times), lang : lang  };
	
}

var results = [];
for ( var index in dir_contents ) {
    
    var dir_name = dir_contents[index];
    var stats = fs.lstatSync(dir_name);
    
    if ( stats.isDirectory() ) {
	var result = process_dir( dir_name );

	if ( result != null ) {
	    results.push(result);
	}
    }

} 
	

results.sort( function( a, b ) {
	return a.avg - b.avg;
    });

fs.writeFileSync( '.report/results.js', 'var results = ' +  JSON.stringify( results ), encoding='utf8' );

