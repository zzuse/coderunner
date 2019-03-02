
#user  nobody;
worker_processes  1;
daemon off;
master_process off;
#error_log logs/error.log debug;
error_log logs/error.log warn;
events {
		worker_connections 1024;
}
http {
		log_format timed_combined '$remote_addr - $remote_user [$time_local] '
		'"$request" $status $body_bytes_sent '
		'"$http_referer" "$http_user_agent" '
		'$request_time $upstream_response_time $pipe';
		access_log logs/access.log timed_combined;

		lua_package_path "/home/zz/opt/lualib/resty/?.lua;;";
		lua_shared_dict state 10m;
		lua_shared_dict mutex 1m;
		lua_shared_dict locks 1m;
		lua_shared_dict config 10m;

		init_by_lua_block {
				local config = require "config"
				local checkups = require "resty.checkups.api"
				checkups.init(config)
		}

		init_worker_by_lua_block {
				local config = require "config"
				local checkups = require "resty.checkups.api"

				checkups.prepare_checker(config)
				checkups.create_checker()
		}

		server {
				listen 192.168.1.137:8081;
				listen 10.0.2.15:8081;
				location / {
						include mime.types;
						root /home/zz/opt/nginx/html;
						index  testdata.json;
				}
		}

		server {
				listen 192.168.1.137:9090;
				listen 10.0.2.15:9090;
				location ~ ^/grafana {
						set $Cookie '';
						#set $my_headers '';
						content_by_lua_block {
								local cjson = require "cjson"
								local action = ngx.var.request_method;
								ngx.req.read_body()
								local data = ngx.req.get_body_data();
								local args = ngx.req.get_uri_args();
								--local headers = {
								--    ["Content-Encoding"] = "deflate",
								--}
 
								if action == "GET" then
										res3 = ngx.location.capture(
												"/sub3"..ngx.var.request_uri,
												{ 
														method = ngx.HTTP_GET, 
														-- body = data
												}
												)
										if res3.status == ngx.HTTP_OK then
												ngx.print(res3.body)
										end
								else
								--ngx.var.my_headers = cjson.encode(headers)
								res1 = ngx.location.capture(
												"/sub1"..ngx.var.request_uri,
												{ 
														method = ngx.HTTP_OPTIONS, 
														body = data
												}
												)

										if res1.status == ngx.HTTP_TEMPORARY_REDIRECT then
												--ngx.print(res1.body)
												--local sampleJson = cjson.encode(res1)
												local metadata = res1.header["Set-Cookie"]
												ngx.req.set_header("Cookie", metadata)
												res2 = ngx.location.capture(
												"/sub2"..ngx.var.request_uri,
												{ 
													method = ngx.HTTP_POST, 
													body = res1.body
												}
												)
												--headers = cjson.decode(ngx.var.my_headers)
												--    for k, v in pairs(headers) do
												--    ngx.header[k] = v
												--end
												if res2.status == ngx.HTTP_OK then
														for k, v in pairs(res2.header) do
																ngx.header[k] = v
														end
														ngx.print(res2.body)
												end
										else
												ngx.print(res1.body)
										end
								end
						}
				}
				location /sub1 {
						rewrite ^/sub1(.*)$ $1 break;  
						proxy_pass http://10.0.2.15:6280;
				}
				location /sub2 {
						rewrite ^/sub2(.*)$ $1 break;
						proxy_pass http://10.0.2.15:6290;
				}
				location /sub3 {
						rewrite ^/sub3(.*)$ $1 break;  
						proxy_pass http://10.0.2.15:6280;
				}
		}
		server {
				listen 10.0.2.15:8080;
				location ~ ^.+sql {
						if ($request_method !~ ^(POST)$) {
								return 444;
						}
						set $vnodeip "";
						set $index -1;
						access_by_lua_block {
								local cjson = require "cjson"
								local jwt = require "resty.jwt"
								local ipconv = require "ipconv"
								local headers = ngx.req.get_headers();
								
								local vpeerDescIp = {}
								if headers["Authorization"] == nil then
										ngx.var.my_upstream = "10.0.2.15"
										ngx.exec("/authorize")
								end
								if headers["Cookie"] == nil then
										ngx.var.my_upstream = "10.0.2.15"
										res1 = ngx.location.capture(
											"/sub1"..ngx.var.request_uri,
											{ 
													method = ngx.HTTP_POST, 
													body = data
											}
											)
										-- subrequest2
										if res1.status == ngx.HTTP_TEMPORARY_REDIRECT then
											local metadata = res1.header["Set-Cookie"]
											ngx.req.set_header("Cookie", metadata)
											res2 = ngx.location.capture(
											"/sub2"..ngx.var.request_uri,
											{ 
												method = ngx.HTTP_POST, 
												body = res1.body
											}
											)
											if res2.status == ngx.HTTP_OK then
													for k, v in pairs(res2.header) do
															ngx.header[k] = v
													end
													ngx.print(res2.body)
											end
										else
												ngx.print(res1.body)
]										end
									end
								else
								    -- subrequest2
									res2 = ngx.location.capture(
									"/sub2"..ngx.var.request_uri,
									{ 
										method = ngx.HTTP_POST, 
										body = res1.body
									}
									)
									if res2.status == ngx.HTTP_OK then
											for k, v in pairs(res2.header) do
													ngx.header[k] = v
											end
											ngx.print(res2.body)
									end
								end
								
						}
						proxy_pass http://$vnodeip:6290;
				}
				location /sub2 {
					rewrite ^/sub2(.*)$ $1 break;
					access_by_lua_block {
					local cookieJson = cjson.encode(headers["Cookie"])
					local metadata = ngx.re.match(cookieJson, ".*,*meta=(.*)\"", "o");
					local decodemeta = ngx.decode_base64(tostring(metadata[1]));
					local jsonmeta = cjson.decode(decodemeta);
					local sid = jsonmeta["metadata"][1];
					vpeerDescIp[1] = jsonmeta["metadata"][2];
					vpeerDescIp[2] = jsonmeta["metadata"][4];
					vpeerDescIp[3] = jsonmeta["metadata"][6];
					vpeerDescIp[4] = jsonmeta["metadata"][8];
					vpeerDescIp[5] = jsonmeta["metadata"][10];
					local index = jsonmeta["metadata"][12];
					local numofcolumn = jsonmeta["metadata"][14];
					ngx.var.vnodeip = ipconv.Dig2Str(vpeerDescIp[index+1]);
					
					if ngx.var.index == -1 then
							ngx.var.index = tonumber(index);
					else
							ngx.var.index = 0
					end
					local checkups = require "resty.checkups.api"
					
					local cb_ok = function(host, port)
					return true
					end
					
					while (tonumber(ngx.var.index)<5)
					do
							local ok, err
							local peer, err = checkups.select_peer(ngx.var.vnodeip)
							if err then
									if peer == nil then
									ok, err = checkups.update_upstream(ngx.var.vnodeip, {
											{
													servers = {
															{host=ngx.var.vnodeip, port=6300, weight=10, max_fails=1, fail_timeout=10},
													}
											},
									})
									end
									ngx.sleep(2)
									ok, err = checkups.ready_ok(ngx.var.vnodeip,cb_ok)
											if not ok then
													ngx.var.index = ngx.var.index + 1
											if vpeerDescIp[ngx.var.index+1] == 0 then
													break
											else
													ngx.var.vnodeip = ipconv.Dig2Str(vpeerDescIp[ngx.var.index+1]);
											end
									end
							else
									break
							end
					end
					}
					proxy_pass http://$vnodeip:6290;
				}
				location @master {
						internal;
						set $my_upstream $my_upstream;
						proxy_pass http://$my_upstream:6280;
				}
				location /authorize {
						internal;
						set $my_upstream $my_upstream;
						proxy_pass http://$my_upstream:6280;
				}
		}
}

